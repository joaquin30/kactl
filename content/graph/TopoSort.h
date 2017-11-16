/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: Topological sorting. Input is a DAG.
 * Output is a topological sorted list of nodes.
 * The function returns false if there is a cycle in the graph.
 * Time: $O(|V|+|E|)$
 */
#pragma once

bool topo_sort(const vector<vi> &edges, vi &sorted, int n) {
	vi indeg(n);
	rep(i,0,n)
		trav(e, edges[i])
			indeg[e]++;
	queue<int> q; // use priority queue for lexic. smallest ans.
	rep(i,0,n) if (indeg[i] == 0) q.push(-i);
	while (sz(q) > 0) {
		int i = -q.front(); // top() for priority queue
		sorted.push_back(i);
		q.pop();
		trav(e, edges[i])
			if (--indeg[e] == 0) q.push(-e);
	}
	return sz(sorted) == n;
}
