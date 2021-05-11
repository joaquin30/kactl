/**
 * Author: Oskar Haarklou Veileborg
 * Date: 2021-05-10
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed sum-tree. Bounds are inclusive to the left and exclusive to the right. Can be changed by modifying T, f and unit.
 * Every update preserves previous versions of the tree.
 * Useful for 3-sided queries in 2D or similar.
 * Usage:
 *  Node* orig = (new Node(0, 2))->update(0, 3);
 *  Node* upd = orig->update(1, 2);
 *  orig->query(0, 2); // = 3
 *  upd->query(0, 2);  // = 5
 * Time: O(\log N)
 * Status: manually tested
 */
#pragma once

#include "../various/BumpAllocator.h"

struct Node {
	typedef int T;
	static constexpr T unit = 0;
	T f(T a, T b) { return a + b; }
	int lo, hi; T v;
	Node *l = 0, *r = 0;
	Node(int lo, int hi) : lo(lo), hi(hi), v(unit) {}
	Node* update(int pos, T val) {
		if(pos < lo || pos >= hi) return this;
		Node* nn = new Node(lo, hi);
		if(lo+1 == hi) nn->v = val;
		else {
			if(!l) {
				int mid = (lo + hi) / 2;
				l = new Node(lo, mid);
				r = new Node(mid, hi);
			}

			nn->l = l->update(pos, val);
			nn->r = r->update(pos, val);
			nn->v = f(nn->l->v, nn->r->v);
		}
		return nn;
	}
	T query(int L, int R) {
		if(L <= lo && hi <= R) return v;
		if(hi <= L || lo >= R || !l) return unit;
		return f(l->query(L, R), r->query(L, R));
	}
};
