/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Self-explanatory methods for string hashing.
 * Status: stress-tested
 */
#pragma once

// Arithmetic mod 2^64-1. 2x slower than mod 2^64 and more
// code, but works on evil test data (e.g. Thue-Morse, where
// ABBA... and BAAB... of length 2^10 hash the same mod 2^64).
// "typedef ull H;" instead if you think test data is random,
// or work mod 10^9+7 if the Birthday paradox is not a problem.
typedef uint64_t ull;
struct H {
	ull x; H(ull x=0) : x(x) {}
	H operator+(H o) { return x + o.x + (x + o.x < x); }
	H operator-(H o) { return *this + ~o.x; }
	H operator*(H o) { auto m = (__uint128_t)x * o.x;
		return H((ull)m) + (ull)(m >> 64); }
	ull get() const { return x + !~x; }
	bool operator==(H o) const { return get() == o.get(); }
	bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11+3; // (order ~ 3e9; random also ok)

vector<H> getHashes(string& str, int length) {
	if (sz(str) < length) return {};
	H h = 0, pw = 1;
	rep(i,0,length)
		h = h * C + str[i], pw = pw * C;
	vector<H> ret = {h};
	rep(i,length,sz(str)) {
		ret.push_back(h = h * C + str[i] - pw * str[i-length]);
	}
	return ret;
}

H hashString(string& s){H h{}; for(char c:s) h=h*C+c;return h;}

struct HashInterval {
	vector<H> ha, pw;
	HashInterval(string& str) : ha(sz(str)+1), pw(ha) {
		pw[0] = 1;
		rep(i,0,sz(str))
			ha[i+1] = ha[i] * C + str[i],
			pw[i+1] = pw[i] * C;
	}
	H hash(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
};

struct HashInterval2 {
	const H C1 = (ll)1e11+3, C2 = (ll)1e11+19;
	vector<vector<H>> ha;
	vector<H> pw1, pw2;
	HashInterval2(vector<string>& str) :
			ha(sz(str)+1, vector<H>(sz(str[0])+1)),
			pw1(sz(str)+1), pw2(sz(str[0])+1) {
		pw1[0] = 1;
		pw2[0] = 1;
		rep(i, 0, sz(str)) pw1[i+1] = pw1[i] * C1;
		rep(i, 0, sz(str[0])) pw2[i+1] = pw2[i] * C2;
		rep(i,0,sz(str)) {
			rep(j, 0, sz(str[0])) {
				ha[i+1][j+1] =
					  ha[i][j+1] * C1
					+ ha[i+1][j] * C2
					- ha[i][j] * C1 * C2
					+ str[i][j];
			}
		}
	}
	H hash(int a, int b, int c, int d) {
		return ha[c][d]
			- ha[a][d] * pw1[c-a]
			- ha[c][b] * pw2[d-b]
			+ ha[a][b] * pw2[d-b] * pw1[c-a];
	}
};
