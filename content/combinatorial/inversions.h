/**
 * Author: Asger Hautop Drewsen
 * Date: 2017-10-03
 * License: CC0
 * Description: Counts the number of inversions in an array.
 * Usage: ll c = invs(arr, 0, sz(arr));
 * Time: O(n \log n)
 */

template <class T>
ll invs(vector<T> & arr, int lo, int hi) {
	if (hi - lo <= 1) return 0;
	int m = (lo + hi) / 2;
	ll r = invs(arr, lo, m) + invs(arr, m, hi);
	vector<T> res(hi - lo);
	auto it = res.begin();
	for (int i = lo, j = m; i < m || j < hi; it++) {
		if (i >= m || (j < hi && arr[i] > arr[j]))
		     *it = arr[j], j++, r += m - i;
		else *it = arr[i], i++;
	}
	copy(all(res), arr.begin() + lo);
	return r;
}
