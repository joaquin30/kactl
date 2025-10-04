/**
 * Author: La Pandilla
 * Date: ??
 * License: CC0
 * Description: A centroid is a node in a tree such that no child subtree
 * has size greater than $n/2$. The height of the decomposition is $\log n$
 * and any path in the original tree $f(u,v)$ can be decomposed into $f(u,w) + f(w,v)$,
 * where $w$ is the LCA of $u$ and $v$ in the decomposition.
 * Time: $O(n \log n)$
 * Status: Tested at CodeForces
 */

const int maxn = 2e5+10;
vector<vi> adj;
bool del[maxn];
int par[maxn]; // parent in centroid decomposition
int szt[maxn]; // size of subtree
int calcsz(int u, int p) {
	szt[u] = 1;
	for (int v : adj[u]) if (v != p && !del[v])
		szt[u] += calcsz(v, u);
	return szt[u];
}
void cdfs(int u = 0, int p = -1, int szu = -1) {
	if (szu < 0) szu = calcsz(u, -1);
	for (int v : adj[u]) {
		if (!del[v] && szt[v] * 2 >= szu) {
			szt[u] = 0;
			cdfs(v, p, szu);
			return;
		}
	}
	del[u] = true;
	par[u] = p;
	// process centroid u
	for (int v : adj[u]) if (!del[v]) cdfs(v, u);
}
void centroid() {
	memset(del, false, sizeof(del));
	cdfs();
}
