/**
 * Author: Simon Lindholm
 * Date: 2015-02-23
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Bellman-Ford_algorithm
 * Description: Calculates shortest paths in a directed graph with non-negative edges
 * Time: O(n \log(n) + m \log(n))
 * Status: Tested on kattis:shortestpath3
 */
#pragma once

const int inf = 1e9;
vector<vector<pii>> adj;
void dijkstra(int s, vi& d, vi& p) {
	d.assign(sz(adj), inf);
	p.assign(sz(adj), -1);
	d[s] = 0;
	priority_queue<pii, vector<pii>, greater<pii>> q;
	q.push({0, s});
	while (!q.empty()) {
		auto [dv, v] = q.top();
		q.pop();
		if (dv != d[v]) continue;
		for (auto [to, len] : adj[v]) {
			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				p[to] = v;
				q.push({d[to], to});
			}
		}
	}
}
