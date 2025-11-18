/**
 * Author: runosake
 * Date: 2017-03-14
 * Source: folklore
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data (lazy).
 * Time: $O(\log N)$
 * Status: stress-tested
 */
#pragma once

const int inf = 1e9;
mt19937 rnd;
struct Node {
	Node *l = 0, *r = 0;
	int val, y, c = 1;
	int msum;
	bool flip = false;
	int mset = inf;
	Node(int val) : val(val), y(rnd()), msum(val) {}
	void recalc();
};
int cnt(Node* n) { return n ? n->c : 0; }
int sum(Node* n) { return n ? n->msum : 0; }
void setLazy(Node* t, int mset) {
	if (!t) return;
	t->mset = mset;
	t->val = mset;
	t->msum = mset * t->c;
}
void flipLazy(Node* t) {
	if (!t) return;
	t->flip ^= 1;
	swap(t->l, t->r);
}
void Node::recalc() {
	c = cnt(l) + cnt(r) + 1;
	msum = val + sum(l) + sum(r);
}
void push(Node* t) {
	if (!t) return;
	if (t->flip) {
		flipLazy(t->l); flipLazy(t->r);
		t->flip = false;
	}
	if (t->mset != inf) {
		setLazy(t->l, t->mset);
		setLazy(t->r, t->mset);
		t->mset = inf;
	}
}
template<class F> void each(Node* n, F f) {
	push(n);
	if (n) { each(n->l, f); f(n->val); each(n->r, f); }
}
pair<Node*, Node*> split(Node* n, int k) {
	if (!n) return {};
	push(n);
	if (cnt(n->l) >= k) { // "n->val >= k" for lower_bound(k)
		auto [L,R] = split(n->l, k);
		n->l = R;
		n->recalc();
		return {L, n};
	} else {
		auto [L,R] = split(n->r,k - cnt(n->l) - 1); // and just "k"
		n->r = L;
		n->recalc();
		return {n, R};
	}
}
Node* merge(Node* l, Node* r) {
	if (!l) return r;
	if (!r) return l;
	push(l), push(r);
	if (l->y > r->y) {
		l->r = merge(l->r, r);
		return l->recalc(), l;
	} else {
		r->l = merge(l, r->l);
		return r->recalc(), r;
	}
}
void del(Node* t) {
	if (!t) return;
	del(t->l); del(t->r);
	delete t;
}
Node* ins(Node* t, Node* n, int pos) {
	auto [l,r] = split(t, pos);
	return merge(merge(l, n), r);
}
// Example application: move the range [l, r) to index k
void move(Node*& t, int l, int r, int k) {
	Node *a, *b, *c;
	tie(a,b) = split(t, l); tie(b,c) = split(b, r - l);
	if (k <= l) t = merge(ins(a, b, k), c);
	else t = merge(a, ins(c, b, k - r));
}
Node* unionn(Node* s, Node* t) {
	if (!s) return t;
	if (!t) return s;
	// push(s); push(t);
	if (s->y < t->y) swap(s, t);
	auto [l, r] = split(t, s->val);
	s->l = unionn(s->l, l);
	s->r = unionn(s->r, r);
	s->recalc();
	return s;
}