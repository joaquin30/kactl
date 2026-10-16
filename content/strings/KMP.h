/**
 * Author: Johan Sannemo
 * Date: 2016-12-15
 * License: CC0
 * Description: pi[x] computes the length of the longest prefix of s that ends at x,
 * other than s[0...x] itself (abacaba -> 0010123).
 * Can be used to find all occurrences of a string or to build an automaton for a single pattern.
 * Time: O(n)
 * Status: Tested on kattis:stringmatching
 */
#pragma once

vi pi(const string& s) {
	vi p(sz(s));
	rep(i,1,sz(s)) {
		int g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}

vi match(const string& s, const string& pat) {
	vi p = pi(pat + '\0' + s), res;
	rep(i,sz(p)-sz(s),sz(p))
		if (p[i] == sz(pat)) res.push_back(i - 2 * sz(pat));
	return res;
}

vector<vi> kmp(const string& pat, int alpha = 26) {
	int m = sz(pat);
	vector<vi> A(m+1, vi(alpha, 0));
	vi p = pi(pat);
	rep(c,0,alpha)
		A[0][c] = (m > 0 && pat[0] == c+'a') ? 1 : 0;
	rep(i,1,m+1) {
		rep(c,0,alpha) {
			if (i < m && pat[i] == c+'a') A[i][c] = i+1;
			else A[i][c] = A[p[i-1]][c]; 
		}
	}
	return A;
}
