/**
 * Author: Lukas Polacek, Joshua Andersson
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Operators for modular arithmetic. You need to set {\tt mod} to
 * some number first and then you can use the structure.
 */
#pragma once

#include "euclid.h"

const ll mod = (119 << 23) + 1; // change to something else
struct Mod {
	ll x;
	Mod(ll y=0) : x(y) {} // be sure that 0 <= y < mod
	Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
	Mod operator-(Mod b) { return Mod((x - b.x + mod) % mod); }
	Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
	Mod operator/(Mod b) { return *this * b.inv(); }
	Mod inv() { // can use *this^(mod-2) if mod is prime
		ll gx, gy, g = euclid(x, mod, gx, gy);
		assert(g == 1); return gx;
	}
	Mod operator^(ll e) {
		if (!e) return 1;
		Mod r = *this ^ (e / 2); r = r * r;
		return e&1 ? *this * r : r;
	}
};
