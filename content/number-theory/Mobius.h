/**
 * Author: chrome
 * Date: 2009-09-25
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53925?#comment-382568
 * Description: Precalculation of Mobius function.
 * Status: Unknown
 */

const int LIM = 5000000;
int mu[LIM], lp[LIM];
void mobius() {
	mu[1] = 1;
	rep(i,2,LIM) {
		if (!lp[i]) for (int j = i; j < LIM; j += i)
			if (!lp[j]) lp[j] = i;
		mu[i] = [](int x) {
			int cnt = 0;
			while (x > 1) {
				int k = 0, d = lp[x];
				while (x % d == 0) {
					x /= d, ++k;
					if (k > 1) return 0;
				}
				++cnt;
			}
			if (cnt & 1) return -1;
			return 1;
		}(i);
	}
}