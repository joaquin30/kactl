/**
 * Author: Noam527
 * Date: 2019-04-24
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

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
ll inv(ll x) { return modpow(x, mod-2); }
