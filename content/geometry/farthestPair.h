/**
 * Author: Ludo Pulles
 * Date: ????
 * Description: Given an ordered convex hull, computes the farthest pair of points.
 * Time: O(n)
 */
#pragma once

#include "Point.h"

double farthestpair(const vector<P> &hull, int &p1, int &p2) {
	int n = sz(hull), a = 0, b = 0;
	if (n == 1) return p1 = p2 = 0;
	auto abcross = [&](){
		return (hull[(a + 1) % n] - hull[a % n]).cross(
		        hull[(b + 1) % n] - hull[b % n]); };
	while (abcross() > 0) b++;
	double res = 0;
	while (a < n) {
		auto d = (hull[a] - hull[b]).dist();
		if (d > res) p1 = a, p2 = b, res = d;
		if (abcross() <= 0) a++;
		else if (++b == n) b = 0;
	}
	return res;
}
