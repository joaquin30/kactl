def ctz(x: int): return (x & -x).bit_length()-1

A = [2, 325, 9375, 28178, 450775, 9780504, 1795265022]
def isPrime(n: int):
	if n < 2 or n % 6 % 4 != 1: return (n | 1) == 3
	s = ctz(n-1)
	d = n >> s
	for a in A:
		p, i = pow(a%n, d, n), s
		while p != 1 and p != n - 1 and a % n:
			i -= 1
			if i == -1: break
			p = p * p % n
		if p != n-1 and i != s: return False
	return True
