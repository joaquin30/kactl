/**
 * Author: chrome
 * Date: 2009-09-25
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53925?#comment-382568
 * Description: Precalculation of Mobius function and iteration over every $d(i)=\lfloor n/i \rfloor$ in $\mathcal{O}(\sqrt{n})$
 * Status: Unknown
 */

int mu[MAXN], lp[MAXN];
mu[1] = 1;
for (int i = 2; i < MAXN; ++i) {
	if (!lp[i]) for (int j = i; j < MAXN; j += i)
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
// iterate every d(i)
for (int i = 1, la; i <= n; i = la + 1) {
	la = n / (n / i);
	// n / x yields the same value for i <= x <= la.
}