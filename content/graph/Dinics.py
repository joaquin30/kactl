'''
 * Author: Oskar Haarklou Veileborg
 * Date: 2019-04-04
 * License: CC0
 * Description: Maximum flow. Very fast in practice.
	To obtain edge flows, compare input and output capacities and discard negative values.
 * Status: Tested on Kattis: gravamen, jupiter, (previous ver: maxflow, mincut, frozenrose, mazemovement)
 * Time: $O(V^2E)$. $O(\sqrt{V}E)$ for bipartite matching.
'''
import sys
from collections import defaultdict
sys.setrecursionlimit(1<<30)

def dinics(graph, s, t):
    assert s != t
    N = len(graph)
    cap = [defaultdict(int, adj) for adj in graph]

    def augment(i, of):
        if i == t: return of
        used, v = 0, valid[i]
        while v and used < of:
            j = v.pop(); c = cap[i][j]
            r = augment(j, min(of - used, c))
            used += r
            cap[i][j] -= r
            cap[j][i] += r
            if 0 < r < c: v.append(j)
        return used

    flow = 0
    while True:
        valid = [[] for _ in range(N)]
        level = [-1] * N
        level[s], Q = 0, [s]
        for i in Q:
            if i == t: break
            for j, c in cap[i].items():
                if level[j] == -1 and c:
                    level[j] = level[i] + 1
                    Q.append(j)
                if level[i] + 1 == level[j] and c:
                    valid[i].append(j)
        else: return flow, cap
        flow += augment(s, float('inf'))
