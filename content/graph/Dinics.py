'''
 * Author: Oskar Haarklou Veileborg
 * Date: 2019-04-04
 * License: CC0
 * Description: Maximum flow. Be careful with the recursion limit - the depth is at most $|V|$, only
	use for graphs with $\sim 1000$ nodes. Very fast in practice.
	To obtain the actual flow, look at positive values only.
 * Status: Tested on Kattis: maxflow, mincut, frozenrose, mazemovement
 * Time: $O(V^2E)$
'''
from collections import deque
class Edge:
	def __init__(self, d, c, r=None):
		self.dest, self.cap, self.rev, self.flow = d, c, r, 0

	def res(self):
		return self.cap - self.flow

class Dinics:
	def __init__(self, N):
		self.N, self.adj = N, [[] for _ in range(N)]

	def add_edge(self, i, j, cap, rcap=0):
		adj = self.adj
		adj[i].append(Edge(j, cap))
		adj[j].append(Edge(i, rcap, adj[i][-1]))
		adj[i][-1].rev = adj[j][-1]

	def maxflow(self, s, t):
		assert s != t
		self.t, flow = t, 0
		while True:
			self.level = level = [None] * self.N
			level[s], Q = 0, deque([s])
			while Q:
				i = Q.popleft()
				if i == t: break
				for e in self.adj[i]:
					if level[e.dest] is None and e.res():
						level[e.dest] = level[i] + 1
						Q.append(e.dest)
			else: return flow
			flow += self.augment(s, float('inf'))

	def augment(self, i, of):
		if i == self.t: return of
		used = 0
		for e in self.adj[i]:
			if self.level[e.dest] != self.level[i] + 1 or not e.res(): continue
			r = self.augment(e.dest, min(of - used, e.res()))
			used += r
			e.flow += r
			e.rev.flow -= r
			if of - used == 0: break
		return used
