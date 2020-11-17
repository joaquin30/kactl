#include "../utilities/template.h"

namespace maximum {
#include "../../content/data-structures/InverseSegmentTree.h"
}

namespace sum {
  struct Tree {
	  typedef int T;
	  static constexpr T unit = 0;
	  T f(T a, T b) { return a + b; } // (any associative, commutative fn)
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
			  if (e % 2) --e, s[e] = f(s[e], val);
		  }
	  }
  };
}


int main() {
	{
		maximum::Tree t(10);
		rep(i, 0, 10) assert(t.query(i) == t.unit);

		t.update(0, 10, 2);
		rep(i, 0, 10) assert(t.query(i) == 2);
	}

	{
		sum::Tree t(10);
		t.update(0, 1, 5);
		assert(t.query(0) == 5);
		rep(i, 1, 10) assert(t.query(i) == 0);

		t.update(0, 10, 1);
		t.update(1, 9, 2);
		assert(t.query(0) == 6);
		rep(i, 1, 9) assert(t.query(i) == 3);
		assert(t.query(9) == 1);
	}

	// Stress maximum
	for(int n = 5; n < 100; n += 5) {
	  maximum::Tree tr(n);
		vi v(n, tr.unit);
		rep(it,0,1000000) {
			int i = rand() % n, j = rand() % (n+1);
			int x = rand() % (n+2);

			int r = rand() % 100;
			if (r < 30) {
				assert(v[i] == tr.query(i));
			}
			else {
				rep(k,i,j) v[k] = max(v[k], x);
				tr.update(i, j, x);
			}
		}
	}

	// Stress sum
	for(int n = 5; n < 100; n += 5) {
		sum::Tree tr(n);
		vi v(n, tr.unit);
		rep(it,0,1000000) {
			int i = rand() % n, j = rand() % (n+1);

			int r = rand() % 100;
			if (r < 30) {
				assert(v[i] == tr.query(i));
			}
			else {
				int x = rand() % (2*n+1) - n;
				rep(k,i,j) v[k] += x;
				tr.update(i, j, x);
			}
		}
	}


	cout<<"Tests passed!"<<endl;
}
