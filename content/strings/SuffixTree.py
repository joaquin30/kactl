r"""
* Author: Oskar Haarklou Veileborg
* Date: 2025-09-10
* License: CC0
* Description: Fast Suffix Tree construction from Suffix Array.
* Status: Stress-tested & tested on Kattis: repeatedsubstrings
* Time: $O(|S| + max(S))$
"""

from __future__ import annotations

# Not golfed

# Suffix Array implementation from PyRival


def SAIS(A: list[int]):
    """
    Calculates suffix array in O(len(A) + max(A))
    Input:
    Int list A with A[i] >= 0 for all i
    """
    n = len(A)
    bs = [0] * (max(A) + 2)
    for a in A:
        bs[a + 1] += 1
    for b in range(1, len(bs)):
        bs[b] += bs[b - 1]
    isL = [1] * n
    for i in reversed(range(n - 1)):
        isL[i] = +(A[i] > A[i + 1]) if A[i] != A[i + 1] else isL[i + 1]

    def isort(LMS):
        SA = [-1] * n
        SA += (n,)
        ep = bs[1:]
        for j in reversed(LMS):
            ep[A[j]] -= 1
            SA[ep[A[j]]] = j
        sp = bs[:-1]
        for i in range(-1, n):
            j = SA[i] - 1
            if j >= 0 and isL[j]:
                SA[sp[A[j]]] = j
                sp[A[j]] += 1
        SA.pop()
        ep = bs[1:]
        for i in reversed(range(n)):
            j = SA[i] - 1
            if j >= 0 and not isL[j]:
                ep[A[j]] -= 1
                SA[ep[A[j]]] = j
        return SA

    isLMS = [+(i and isL[i - 1] and not isL[i]) for i in range(n)]
    isLMS.append(1)
    LMS = [i for i in range(n) if isLMS[i]]
    if len(LMS) > 1:
        SA = isort(LMS)
        LMS2 = [i for i in SA if isLMS[i]]
        prev = -1
        j = 0
        for i in LMS2:
            i1 = prev
            i2 = i
            while prev >= 0 and A[i1] == A[i2]:
                i1 += 1
                i2 += 1
                if isLMS[i1] or isLMS[i2]:
                    j -= isLMS[i1] and isLMS[i2]
                    break
            j += 1
            prev = i
            SA[i] = j
        LMS = [LMS[i] for i in SAIS([SA[i] for i in LMS])]
    return isort(LMS)


def KASAI(A: list[int], SA: list[int]):
    """
    Calculates LCP array in O(n) time
    Input:
    String A and its suffix array SA
    """
    n = len(A)
    rank = [0] * n
    for i in range(n):
        rank[SA[i]] = i
    LCP = [0] * (n - 1)
    k = 0
    for i in range(n):
        SAind = rank[i]
        if SAind == n - 1:
            continue
        j = SA[SAind + 1]
        while i + k < n and A[i + k] == A[j + k]:
            k += 1
        LCP[SAind] = k
        k -= k > 0
    return LCP


class Tree:
    __slots__ = "adj", "e", "leaves", "s"

    def __init__(self, SA: list[int]):
        N = len(SA)
        self.s = SA[:]
        self.e = [N] * N
        self.adj: list[list[int]] = [[] for _ in range(N)]
        self.leaves = [1] * N

    def new(self, s: int, e: int, nxt: int) -> int:
        self.s += (s,)
        self.e += (e,)
        self.adj += ([nxt],)
        self.leaves += (self.leaves[nxt],)
        return len(self) - 1

    def size(self, i: int) -> int:
        return self.e[i] - self.s[i]

    def __len__(self):
        return len(self.s)

    @property
    def root(self) -> int:
        return len(self) - 1

    def show(self, S: str):
        import subprocess
        import sys

        lines = ["digraph {"]
        O = [self.root]
        for i in O:
            lines.append(f'  {i} [label="{i}\\n{S[self.s[i] : self.e[i]]}"];')
            lines.extend(f"  {i} -> {c};" for c in self.adj[i])
            O += self.adj[i]
        lines.append("}")
        input = "\n".join(lines)
        print(input, file=sys.stderr)
        subprocess.run(["xdot", "-"], input=input, text=True, capture_output=True, check=True)


def suffix_tree(A: list[int]):
    """
    O(N + max(A)) Suffix Tree construction from Suffix Array.
    Performs a bottom-up traversal of the suffix tree by merging
    suffixes in reverse order of their LCP values.
    Many problems can be solved directly during this traversal
    instead of building the tree explicitly.
    """
    SA = SAIS(A)
    LCP = KASAI(A, SA)
    N = len(A)
    node = list(range(N))
    t = Tree(SA)

    def cut(i: int, lcp: int):
        "Cut the root node of tree i into two parts at depth lcp."
        assert lcp <= depth[i]
        if lcp != depth[i]:
            n = node[i]
            assert t.s[n] == SA[i] and t.e[n] == SA[i] + depth[i]
            t.s[n] = SA[i] + lcp
            node[i] = t.new(SA[i], t.s[n], n)

    left = list(range(N))
    right = left[:]
    depth = [N - i for i in SA]
    # Bucket sort is not faster
    for x in sorted([(l << 32) | i for i, l in enumerate(LCP)], reverse=True):
        j = x & ((1 << 32) - 1)
        lcp = LCP[j]
        i, j = j + 1, left[j]
        r = right[j] = right[i]
        left[r] = j

        cut(i, lcp)
        cut(j, lcp)
        a, b = node[i], node[j]
        # assert A[a.s : a.e] == A[b.s : b.e]
        t.adj[b].extend(t.adj[a])
        t.leaves[b] += t.leaves[a]
        depth[j] = lcp

    cut(0, 0)
    assert t.root == node[0] and t.size(t.root) == 0
    return t


def repeatedsubstrings(S: str):
    """
    Finds the longest substring that occurs at least twice in S.
    If multiple solutions exist, returns the lexicographically smallest.
    """
    A = [ord(c) for c in S]
    t = suffix_tree(A)
    M = len(t)
    parent = [-1] * M
    size = [0] * M
    stack = [t.root]
    O: list[int] = []
    while stack:
        n = stack.pop()
        O += (n,)
        for c in reversed(t.adj[n]):
            parent[c] = n
            size[c] = size[n] + t.size(c)
            stack.append(c)

    # t.show(S)

    n = max((n for n in O if t.leaves[n] >= 2), key=lambda x: size[x], default=-1)
    ans: list[str] = []
    while n >= 0:
        ans.append(S[t.s[n] : t.e[n]])
        n = parent[n]

    print("".join(reversed(ans)))


def longest_common_substring(S: str, T: str):
    """Finds the length of the longest common substring between S and T."""
    A = [ord(c) for c in S] + [0] + [ord(c) for c in T] + [1]
    t = suffix_tree(A)
    M = len(t)
    size = [0] * M
    mask = [0] * M
    O = [t.root]
    for n in O:
        if t.s[n] <= len(S) < t.e[n]:
            mask[n] = 1
        elif t.e[n] == len(A):
            mask[n] = 2

        for c in t.adj[n]:
            size[c] = size[n] + t.size(c)
            O += (c,)

    for n in reversed(O):
        for c in t.adj[n]:
            mask[n] |= mask[c]

    return max((size[n] for n in O if mask[n] == 3), default=0)
