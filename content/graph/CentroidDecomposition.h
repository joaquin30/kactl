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
vector<vi> adj;
bool tk[MAXN];
int par[MAXN]; // parent in centroid decomposition
int szt[MAXN]; // size of subtree
int calcsz(int x, int f) {
	szt[x] = 1;
	for (auto y : adj[x]) 
		if (y != f && !tk[y])
			szt[x] += calcsz(y, x);
	return szt[x];
}
void cdfs(int x = 0, int f = -1, int sze = -1) { // O(nlogn)
	if (sze < 0) sze = calcsz(x, -1);
	for (auto y : adj[x]) {
		if (!tk[y] && szt[y] * 2 >= sze) {
			szt[x] = 0;
			cdfs(y, f, sze);
			return;
		}
	}
	tk[x] = true;
	par[x] = f;
	for (auto y : adj[x]) if (!tk[y]) cdfs(y, x);
}
void centroid() {
	memset(tk, false, sizeof(tk));
	cdfs();
}
