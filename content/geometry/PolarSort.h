/**
 * Author: Victor Lecomte
 * Date: 2009-02-26
 * License: Unknown
 * Source: Handbook of geometry for competitive programmers
 * Description: Sort a list of points ccw around an origin.
 * Time: O(n \log n)
 * Status: Unknown
 */

typedef Point<ll> P;
bool half(P p) {
	assert(p.x != 0 || p.y != 0);
	return p.y > 0 || (p.y == 0 && p.x < 0);
}
void polarSort(vector<P> &v, P o) {
	sort(all(v), [](P v, P w) {
		return make_tuple(half(v-o), 0) <
			make_tuple(half(w-o), (v-o).cross(w-o));
	});
}