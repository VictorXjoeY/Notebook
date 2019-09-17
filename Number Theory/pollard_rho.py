from random import randint
from math import gcd

# O(N) - Returns the prime numbers up to n.
def linear_sieve(n):
	# mp[i] stores the minimum prime number which divides i. i is prime if it's not 0 and mp[i] == i.
	mp = [0 for i in range(n + 1)]
	p = []

	for i in range(2, n + 1):
		if mp[i] == 0: # i is prime if we haven't found any smaller factors of it.
			mp[i] = i
			p.append(i)
		
		# Since every number x can be written as x = i * mp[x] we can iterate over every prime mp[x] (prime[j]).
		j = 0

		while j < len(p) and p[j] <= mp[i] and i * p[j] <= n:
			mp[i * p[j]] = p[j]
			j += 1

	return p

# O(Log(N)) - Returns true if n is probably prime and returns false if it composite for sure.
def is_probably_prime(n, a, d, s):
	x = pow(a, d, n)

	# a^d = 1 (mod n)
	if x == 1:
		return True

	# a^(d * 2^r) = -1 (mod n), 0 <= r < s
	for r in range(s):
		if x == n - 1:
			return True

		x = (x * x) % n

	return False

# O(K + |Primes <= K| * Log(N)) - Returns true if n is probably prime and returns false otherwise.
def miller_rabin(n, k = 100):
	a = linear_sieve(k)

	if n <= 1:
		return False

	# If n is among the first few primes.
	if n in a:
		return True

	# O(Log(N) - Decomposing n - 1 = d * 2^s
	s = 0
	d = n - 1

	while d % 2 == 0:
		d //= 2
		s += 1

	# For each prime base a[i].
	for i in range(len(a)):
		if not is_probably_prime(n, a[i], d, s):
			return False

	return True

# O(1) - Returns f(x) = x^2 + c.
def f(x, c, n):
	return (x * x + c) % n

# O(N^(1/4) * Log(N)) - Finds a divisor 1 < d < n of n. Expects a composite number.
def pollard_rho(n):
	if n % 2 == 0:
		return 2

	# Randomizing values for x0 and c for the polynomial f(x) = x^2 + c.
	tortoise = randint(2, n - 1)
	hare = tortoise
	c = randint(1, n - 1)
	g = 1

	while g == 1:
		tortoise = f(tortoise, c, n)
		hare = f(f(hare, c, n), c, n)
		g = gcd(abs(hare - tortoise), n)

	# Failed to find a divisor. Trying again.
	if g == n:
		return pollard_rho(n)

	# Found a divisor.
	return g

# O(N^(1/4) * Log(N)).
def factorization(n, p):
	# No prime factors.
	if n == 1:
		return

	# Prime.
	if miller_rabin(n):
		p.append(n)
		return

	# Composite.
	d = pollard_rho(n)
	factorization(d, p)
	factorization(n // d, p)


# O(N^(1/4) * Log(N)).
def factor(n):
	# Factorizing.
	p = []
	factorization(n, p)
	p.sort()

	# Retrieving exponents.
	f = []

	for i in range(len(p)):
		if len(f) > 0 and p[i] == f[-1][0]:
			f[-1][1] += 1
		else:
			f.append([p[i], 1])

	return f