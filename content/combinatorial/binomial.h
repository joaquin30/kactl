/**
 * Author: See source
 * Date: 2024-10-22
 * Source: https://cp-algorithms.com/combinatorics/binomial-coefficients.html
 * Description: Computes $C(n,k)$. Can be used with double and mod.
 * Time: O(\min(k,n-k))
 * Status: Unknown
 */

int C(int n, int k) {
	if (n < k || k < 0) return 0;
	if (n - k < k) k = n - k;
	int res = 1;
	rep(i,1,k+1) res = res * (n - k + i) / i;
	return res; // res + 0.01 for double
}
