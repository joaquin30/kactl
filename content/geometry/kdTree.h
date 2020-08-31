/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook
 * Description: KD-tree (any dimension)
 * Status: Tested on excellentengineers
 */
#pragma once

using T = long long;
constexpr int DIM = 2;
using P = array<T, DIM>;
const T INF = numeric_limits<T>::max();

struct Node {
	P pt; // if this is a leaf, the single point in it
	P lo_bound, hi_bound;
	Node *first = 0, *second = 0;

	T distance(const P& p) { // min squared distance to a point
		T r = 0;
		rep(i, 0, DIM) {
			T d = p[i] - max(lo_bound[i], min(hi_bound[i], p[i]));
			r += d * d;
		}
		return r;
	}

	Node(vector<P>&& vp) : pt(vp[0]) {
		rep(i, 0, DIM) {
			lo_bound[i] = INF; hi_bound[i] = -INF;
		}
		for (const P & p : vp) {
			rep(i, 0, DIM) {
				lo_bound[i] = min(lo_bound[i], p[i]);
				hi_bound[i] = max(hi_bound[i], p[i]);
			}
		}
		if (sz(vp) > 1) {
			// split on x if width >= height (not ideal...)
			pair<T, int> biggest = {-1, -1};
			rep(i, 0, DIM)
				biggest = max(biggest, {hi_bound[i] - lo_bound[i], i});
			int i = biggest.second;
			sort(all(vp), [&](const P& a, const P& b){ return a[i] < b[i]; });
			// divide by taking half the array for each child (not
			// best performance with many duplicates in the middle)
			int half = sz(vp)/2;
			first = new Node({vp.begin(), vp.begin() + half});
			second = new Node({vp.begin() + half, vp.end()});
		}
	}
};

struct KDTree {
	Node* root;
	KDTree(const vector<P>& vp) : root(new Node({all(vp)})) {}

	pair<T, P> search(Node *node, const P& p) {
		if (!node->first) {
			// uncomment if we should not find the point itself:
			// if (p == node->pt) return {INF, P()};
			return {node->distance(p), node->pt};
		}

		Node *f = node->first, *s = node->second;
		T bfirst = f->distance(p), bsec = s->distance(p);
		if (bfirst > bsec) swap(bsec, bfirst), swap(f, s);

		// search closest side first, other side if needed
		auto best = search(f, p);
		if (bsec < best.first)
			best = min(best, search(s, p));
		return best;
	}

	// find nearest point to a point, and its squared distance
	// (requires an arbitrary operator< for Point)
	pair<T, P> nearest(const P& p) {
		return search(root, p);
	}
};
