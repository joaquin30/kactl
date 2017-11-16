/**
 * Author: Asger Hautop Drewsen
 * Date: 2017-10-26
 * License: CC0
 * Description: Class for rational arithmetic
 */
#pragma once

#include "euclid.h"

template <typename T>
struct Rational {
	using R = Rational<T>;
	T n, d;
	Rational(T _n) : n(_n), d(1) {}
	Rational(T _n, T _d): n(_n), d(_d) {
		T g = gcd(n, d);
		n /= g, d /= g;
		if (d < 0) n *= -1, d *= -1;
		assert(d != 0);
	}
	R operator+(R o) const {
		T l = lcm(d, o.d);
		return {n * (l / d) + o.n * (l / o.d), l};
	}
	R operator-() const { return {-n, d}; }
	R operator-(R o) const { return *this + (-o); }
	R operator*(R o) const { return {n * o.n, d * o.d}; }
	R operator/(R o) const { return *this * R(o.d, o.n); }
	bool operator==(R o) const {
		return tie(n, d) == tie(o.n, o.d);
	}
	bool operator<(R o) const {
		return (*this - o).n < 0;
	}
};
