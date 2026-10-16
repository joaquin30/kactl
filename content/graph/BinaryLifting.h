/**
 * Author: Johan Sannemo
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Calculate power of two jumps in a tree,
 * to support fast upward jumps and LCAs.
 * Assumes the root node points to itself.
 * Time: construction $O(N \log N)$, queries $O(\log N)$
 * Status: Tested at Petrozavodsk, also stress-tested via LCA.cpp
 */
#pragma once

vector<vi> adj, tbl;
vi depth;

void dfs(int v, int p) {
	depth[v] = depth[p] + 1;
	tbl[0][v] = p;
	rep(i,1,sz(tbl)) tbl[i][v] = tbl[i-1][tbl[i-1][v]];
	for (int u : adj[v]) if (u != p) dfs(u, v);
}

void binLifting(int root) {
	int on = 1, d = 1, n = sz(adj);
	while (on < n) on *= 2, d++;
	tbl.assign(d, vi(n));
	depth.assign(n, -1);
	dfs(root, root);
}

int jmp(int nod, int steps) {
	rep(i,0,sz(tbl))
		if (steps & (1<<i)) nod = tbl[i][nod];
	return nod;
}

int lca(int a, int b) {
	if (depth[a] < depth[b]) swap(a, b);
	a = jmp(tbl, a, depth[a] - depth[b]);
	if (a == b) return a;
	for (int i = sz(tbl); i--;) {
		int c = tbl[i][a], d = tbl[i][b];
		if (c != d) a = c, b = d;
	}
	return tbl[0][a];
}
