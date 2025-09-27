/**
 * Author: Darren Yao, Abutalib Namazov, Andrew Wang, Qi Wang, Dustin Miao
 * Date: 2024-10-09
 * License: CC0
 * Source: https://usaco.guide/silver/binary-search
 * Description:
 * Find the first or last $i$ in $[a,b]$ such that $f(i)$ is true, assuming that $f$ is monotonically increasing or decreasing.
 * If real values are needed change int to double and iterate 100-200 times.
 * Usage:
	int ind = firstTrue(0,n-1,[\&](int i){return a[i]<x;});
 * Time: O(\log(b-a))
 * Status: tested
 */
#pragma once

template<class F>
int lastTrue(int a, int b, F f) {
	assert(a <= b), --a;
	while (a < b) {
		int mid = a + (b - a + 1) / 2;
		if (f(mid)) a = mid;
		else b = mid - 1;
	}
	return a;
}
template<class F>
int firstTrue(int a, int b, F f) {
	assert(a <= b), ++b;
	while (a < b) {
		int mid = a + (b - a) / 2;
		if (f(mid)) b = mid;
		else a = mid + 1;
	}
	return a;
}
