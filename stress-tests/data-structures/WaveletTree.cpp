#include "../utilities/template.h"

#include "../../content/data-structures/WaveletTree.h"

pii randInterval(int max) {
	int l = rand() % max;
	return {l, l + rand() % (max - l) + 1};
}

int main() {
	srand(time(nullptr));

	for(int n = 5; n < 1000; n += 5) {
		vi v;
		rep(i, 0, n) v.push_back(rand() % n);
		Node root(v, 0, n);

		// Test quantile
		rep(it, 0, 1'000) {
			auto [l, r] = randInterval(n);
			int k = rand() % (r - l);

			vi S(v.begin() + l, v.begin() + r);
			sort(all(S));
			assert(root.quantile(k, l, r) == S[k]);
		}

		// Test rank
		rep(it, 0, 1'000) {
			int r = rand() % n + 1;
			int x = rand() % n;

			int cnt = 0;
			rep(i, 0, r) cnt += v[i] == x;
			assert(root.rank(x, r) == cnt);
		}

		// Test rectangle
		rep(it, 0, 1'000) {
			auto [l, r] = randInterval(n);
			auto [a, b] = randInterval(n);

			int cnt = 0;
			rep(i, l, r) if(a <= v[i] && v[i] < b) cnt++;
			assert(root.rectangle(a, b, l, r) == cnt);
		}
	}

	cout<<"Tests passed!"<<endl;
}
