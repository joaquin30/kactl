/**
 * Author: Oskar Haarklou Veileborg
 * Date: 2021-05-28
 * License: CC0
 * Source: https://users.dcc.uchile.cl/~jperez/papers/ioiconf16.pdf
 * Description: Tree that recursively partitions a sequence into subsequences by value.
 * $\sigma$ is the difference between the largest and smallest element in the sequence
 * (pre-compress values if $\sigma$ is large).
 * Use with a bump allocator for better performance.
 * Time: O(\log \sigma). \textbf{Space:} O(N \log \sigma).
 * Usage: auto [lo, hi] = minmax_element(all(A));
 * Node tr(A, *lo, (*hi)+1);
 * Status: Stress-tested and tested on kattis: anothersubstringqueryproblem (quantile)
 * Details: Can probably be transformed to a non-pointer version for better performance.
 */
#pragma once

struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;	vi C; // C[i] = # of first i elements going left
	Node(const vi& A, int lo, int hi) : lo(lo), hi(hi), C(1, 0) {
		if(lo + 1 == hi) return;
		int mid = (lo + hi) / 2;
		vi L, R;
		for(int a: A) {
			C.push_back(C.back());
			if(a < mid) L.push_back(a), C.back()++;
			else R.push_back(a);
		}
		l = new Node(L, lo, mid), r = new Node(R, mid, hi);
	}
	// k'th (0-indexed) element in the sorted range [L, R)
	int quantile(int k, int L, int R) {
		if(lo + 1 == hi) return lo;
		int c = C[R] - C[L];
		if(k < c) return l->quantile(k, C[L], C[R]);
		return r->quantile(k - c, L - C[L], R - C[R]);
	}
	// number of elements in range [0, R) equal to x
	int rank(int x, int R) {
		if(lo + 1 == hi) return R;
		if(x < l->hi) return l->rank(x, C[R]);
		return r->rank(x, R - C[R]);
	}
	// number of elements x in range [L, R) st. a <= x < b
	int rectangle(int a, int b, int L, int R) {
		if(a <= lo && hi <= b) return R - L;
		if(a >= hi || b <= lo) return 0;
		return l->rectangle(a, b, C[L], C[R]) +
			r->rectangle(a, b, L - C[L], R - C[R]);
	}
};
