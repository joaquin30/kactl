'''
 * Author: Oskar Haarklou Veileborg
 * Date: 2019-04-04
 * License: CC0
 * Description: Maximum flow. Very fast in practice.
	To obtain the actual flow, compare input and output capacities.
 * Status: Tested on Kattis: maxflow, mincut, frozenrose, mazemovement
 * Time: $O(V^2E)$
'''
import sys
from collections import deque, defaultdict
sys.setrecursionlimit(1<<30)

def dinics(graph, s, t):
    assert s != t
    N = len(graph)
    cap = [defaultdict(int, adj) for adj in graph]

    def augment(i, of):
        if i == t: return of
        used = 0
        for j, c in cap[i].items():
            if level[j] != level[i] + 1 or not c: continue
            r = augment(j, min(of - used, c))
            used += r
            cap[i][j] -= r
            cap[j][i] += r
            if of == used: break
        return used

    flow = 0
    while True:
        level = [-1] * N
        level[s], Q = 0, deque([s])
        while Q:
            i = Q.popleft()
            if i == t: break
            for j, c in cap[i].items():
                if level[j] == -1 and c:
                    level[j] = level[i] + 1
                    Q.append(j)
        else: return flow, cap
        flow += augment(s, float('inf'))
