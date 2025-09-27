/**
 * Author: Matheus Pimenta
 * License: CC0
 * Source: https://codeforces.com/blog/entry/49812
 * Description: Knapsack over a multiset.
 * ms[i].first ($a_i$) is the number and ms[i].second ($b_i$) is the count.
 * Useful when $\sum_i a_i \cdot b_i = \mathcal{O}(n)$
 * Time: O(\sqrt{n} \cdot n / 32)
 * Status: Tested on kattis:eavesdropperevasion, stress-tested
 */
#pragma once

typedef bitset<maxn> bs;
bs knapsack(const vector<pii>& ms) {
	bs dp;
	dp[0] = 1;
	for (auto [a, b] : ms) {
		for (int x = 0; (1<<x) <= b; x++) {
			dp |= (dp << (a*(1<<x)));
			b -= (1<<x);
		}
		dp |= (dp << (a*b));
	}
	return dp;
}
