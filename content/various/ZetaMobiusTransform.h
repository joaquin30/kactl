/**
 * Author: Park Jinhan
 * License: CC0
 * Source: https://codeforces.com/blog/entry/119082
 * Description: Zeta and Mobius transform to convert from and to functions $g(t) = \sum_{s \preceq t} f(s)$,
 * where the $s \preceq t$ relation could be subset ($s \subseteq t$), superset ($s \supseteq t$), divisor ($s|t$) or multiple ($t|s$).
 * \texttt{PrimeEnumerate(n)} are all the primes less or equal than $n$.
 * Time: O(K 2^K) \text{or} O(N \log \log N)
 * Status: stress-tested
 */
#pragma once

template<class T>
void SubsetZetaTransform(vector<T>& v) {
	const int n = v.size(); // n must be a power of 2 (2^K)
	for (int j = 1; j < n; j <<= 1) {
		for (int i = 0; i < n; i++)
			// swap position of v[i] and v[i^j] for superset
			// change to -= for mobius
			if (i & j) v[i] += v[i ^ j];
	}
}
template<class T>
void MultipleZetaTransform(vector<T>& v) {
	const int n = (int)v.size() - 1;
	for (int p : PrimeEnumerate(n)) {
		// for divisor zeta and multiple mobius
		// for (int i = 1; i * p <= n; i++)
		// for divisor mobius and multiple zeta
		for (int i = n / p; i; i--)
			// swap position of v[i] and v[i*p] for divisor
			// change to -= for mobius
			v[i] += v[i * p];
	}
}
