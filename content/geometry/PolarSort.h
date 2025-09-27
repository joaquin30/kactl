/**
 * Author: Victor Lecomte
 * Date: 2009-02-26
 * License: Unknown
 * Source: Handbook of geometry for competitive programmers
 * Description: Sort a list of points ccw around an origin.
 * Time: O(n \log n)
 * Status: Unknown
 */

bool half(pt p) {
	assert(p.x != 0 || p.y != 0);
	return p.y > 0 || (p.y == 0 && p.x < 0);
}
void polarSort(vector<pt> &v, pt o) {
	sort(all(v), [](pt v, pt w) {
		return make_tuple(half(v-o), 0)) <
			make_tuple(half(w-o), (v-o).cross(w-o));
	});
}