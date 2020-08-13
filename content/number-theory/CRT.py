"""
 * Author: Asger Hautop Drewsen
 * Date: 2020-08-13
 * License: CC0
 * Description: Chinese Remainder Theorem. \texttt{crt(r, m)} computes $x$ such that $x \equiv r_i \pmod{m_i}$ for all $i$ and $0 \leq x < \mathrm{lcm}(m)$.
 * Status: Tested on substitution and fuzz-checked against sage.
 * Time: $\sum_i \log(m_i)$
"""


def euclid(a, b):
    if not b: return a, 1, 0
    d, y, x = euclid(b, a % b)
    return d, x, y - a // b * x

def crt2(a, b, m, n):
    if n > m: a, b, m, n = b, a, n, m
    g, x, y = euclid(m, n)
    assert (a - b) % g == 0
    x = (b - a) % n * x % n // g * m + a
    return x, g

def crt(rem, mod):
    a, m = 0, 1
    for b, n in zip(rem, mod):
        g, x, y = euclid(m, n)
        a, g = crt2(a, b, m, n)
        m = m // g * n
    return a
