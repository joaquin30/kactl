/**
 * Author: Asger Hautop Drewsen
 * Date: 2021-02-02
 * License: CC0
 * Description: Calculates the chromatic number of an undirected graph.
 * Time: $O(2.4422^n)$
 * Status: Tested on committeeassignment
 */
#include "MaximalCliques.h"

const int MAXN = 15;
int memo[1<<MAXN] = {0};
int aux(vector<B>& eds, B nodes) {
	auto k = nodes.to_ulong();
	if (!nodes.any()) return 0;
	if (memo[k]) return memo[k];
	int r = MAXN;
	cliques(eds, [&](B x) {
		r = min(r, 1 + aux(eds, nodes & ~x));
	}, nodes);
	return memo[k] = r;
}
int chromaticNumber(vector<B>& eds) {
	vector<B> comp;
	rep(i, 0, sz(eds)) comp.push_back((~eds[i]).reset(i));
	return aux(comp, (1 << sz(comp)) - 1);
}
