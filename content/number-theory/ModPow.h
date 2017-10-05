/**
 * Author: Simon Lindholm
 * Date: 2016-09-10
 * License: CC0
 * Source: folklore
 * Description: If $e$ is really large and the base $m$ is small use $a^{\varphi(m)} \equiv 1 \mod m$ for $gcd(a, m) = 1$.
 * So $a^{e} \equiv a^{e \mod \varphi(m)} \mod m$.
 * For $gcd(a, m) \neq 1$ set $g = gcd(a, m)$, $x = e \mod \varphi(m)$. If $e = 0$ return 1. \\
 * Otherwise $a^{e} \equiv (g^{x} \mod m) ((a / g)^{x} \mod m) \mod m$.
 * Status: tested
 */
#pragma once

const ll mod = 1000000007; // faster if const
ll modpow(ll a, ll e) {
	if (e == 0) return 1;
	ll x = modpow(a * a % mod, e >> 1);
	return e & 1 ? x * a % mod : x;
}
