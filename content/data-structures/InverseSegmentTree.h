/**
 * Author: Lucian Bicsi, Oskar Haarklou Veileborg
 * Date: 2020-11-17
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree with range updates and point queries.
 * Bounds are inclusive to the left and exclusive to the right. Can be changed by modifying T, f and unit.
 * More limited than LazySegmentTree but much better constant factors.
 * Update performs: $a[i] = f(a[i], val), i \in [b,e)$ where $a$ is the underlying array.
 * Time: O(\log N)
 * Status: stress-tested
 * Details: See stress tests for applications.
 */
#pragma once

struct Tree {
	typedef int T;
	static constexpr T unit = INT_MIN;
	// (any associative, commutative fn)
	T f(T a, T b) { return max(a, b); }
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	T query(int pos) {
	  T res = s[pos += n];
	  while(pos /= 2) res = f(res, s[pos]);
	  return res;
	}
	void update(int b, int e, T val) { // update [b, e)
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) s[b] = f(val, s[b]), b++;
			if (e % 2) --e, s[e] = f(val, s[e]);
		}
	}
};
