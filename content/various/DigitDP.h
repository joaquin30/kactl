
/**
 * Author: Jon.Snow
 * License: CC0
 * Source: https://codeforces.com/blog/entry/77096
 * Description: DP on digits. The code is an example to count numbers between 0 and $K$ such that
 * the sum of its digits is prime. The string is $K$ converted.
 * Status: tested on http://codeforces.com/contest/321/problem/E
 */
int dp[20][2][200];
int digit_dp(const string& s) {
	int n = sz(s);
	//empty suffixes having sum=0
	dp[n][0][0] = 1;
	dp[n][1][0] = 1;
	for (int i = n-1; i >= 0; i--) {
		rep(sum,0,200) {
			for (int d = 0; d < 10; d++) {
				dp[i][0][sum] += dp[i+1][0][sum-d];
			}
		}
		rep(sum,0,200) {
			for (int d = 0; d <= s[i] - '0'; d++) {
				dp[i][1][sum] += (d == s[i]-'0') ?
					dp[i+1][1][sum-d] : dp[i+1][0][sum-d];
			}
		}
	}
	int ans = 0;
	rep(i,0,200) {
		if (isPrime(i))
			ans += dp[0][1][i];
	}
	return ans;
}