from random import randint
from math import gcd

# O(Log(min(a, b))) - Extended Euclidean Algorithm.
# Returns a solution to a * x + b * y = gcd(a, b).
# Returns |x| <= |a / gcd(a, b)|, |y| <= |b / gcd(a, b)| and gcd(a, b).
def extended_gcd(a, b):
	if a == 0:
		return (b, 0, 1)

	gcd, x, y = extended_gcd(b % a, a)

	return (gcd, y - (b // a) * x, x)

# O(Log(min(a, b))).
# a * x + b * y = c
# 	x = x1 + k * (b / gcd(a, b))
# 	y = y1 - k * (a / gcd(a, b))
# 
# a * x - b * y = c ---> a * x + b * (-y) = c
# 	x = x1 + k * (b / gcd(a, b))
# 	-y = y1 - k * (a / gcd(a, b)) ---> y = -y1 + k * (a / gcd(a, b))
# 
# -a * x + b * y = c ---> a * (-x) + b * y = c
# 	-x = x1 + k * (b / gcd(a, b)) ---> x = -x1 - k * (b / gcd(a, b))
# 	y = y1 - k * (a / gcd(a, b))
# 
# -a * x - b * y = c ---> a * (-x) + b * (-y) = c
# 	-x = x1 + k * (b / gcd(a, b)) ---> x = -x1 - k * (b / gcd(a, b))
# 	-y = y1 - k * (a / gcd(a, b)) ---> y = -y1 + k * (a / gcd(a, b))
# 
# Use positive values for a and b for this function.
# Has infinite solutions if and only if gcd(a, b) divides c.
# If a and/or b are 0, treat those cases separately.
def diophantine(a, b, c):
	# Obtaining a * x1 + b * y1 = gcd(a, b)
	gcd, x, y = extended_gcd(a, b)

	# No solution
	if c % gcd != 0:
		return (0, 0, 0)

	# Multiplying the above equation by k = c / gcd to obtain a * x1 + b * y1 = c
	return (gcd, x * (c // gcd), y * (c // gcd))

# O(N * Log(lcm(m1, m2, ..., mn))) - General Chinese Remainder Theorem.
# 
# Considering the following family of linear congruences:
# 
# t = a1 (mod m1)
# t = a2 (mod m2)
# ...
# t = an (mod mn)
# 
# Returns the smallest non-negative solution modulo lcm(m1, m2, ..., mn). Returns -1 if there is no solution.
# 
# The family of linear congruences has a solution if and only if every pair of linear congruences is consistent.
# A pair of linear congruences is consistent if a1 = a2 (mod gcd(m1, m2)).
# 
# t = a1 (mod m1) ---> t - a1 = m1 * x
# t = a2 (mod m2) ---> t - a2 = m2 * y
# 
# a1 + m1 * x = a2 + m2 * y
# m1 * x - m2 * y = a2 - a1
# m1 * x + m2 * (-y) = a2 - a1
# 
# x = x1 + k * m2 / gcd(m1, m2)
# y = -y1 + k * m1 / gcd(m1, m2)
# 
# t - a1 = m1 * (x1 + k * m2 / gcd(m1, m2))
# t - a1 = m1 * x1 + lcm(m1, m2) * k
# t - (a1 + m1 * x1) = lcm(m1, m2) * k ---> t = a1 + m1 * x1 (mod lcm(m1, m2))
# 
# t - a2 = m2 * (-y1 + k * m1 / gcd(m1, m2))
# t - a2 = -m2 * y1 + lcm(m1, m2) * k
# t - (a2 - m2 * y1) = lcm(m1, m2) * k ---> t = a2 - m2 * y1 (mod lcm(m1, m2))
def chinese_remainder_theorem(a, m):
	# Making 0 <= ai < mi.
	for i in range(len(a)):
		a[i] = ((a[i] % m[i]) + m[i]) % m[i]

	a1, m1 = 0, 1

	for i in range(len(a)):
		a2, m2 = a[i], m[i]

		# Solving m1 * x + m2 * (-y) = a2 - a1
		gcd, x1, y1 = diophantine(m1, m2, a2 - a1)

		if gcd == 0: # No solution.
			return (-1, 0)

		# Calculating lcm(m1, m2).
		lcm = (m1 * m2) // gcd

		# Updating answer.
		a1 = ((a1 + m1 * x1) % lcm + lcm) % lcm
		m1 = lcm

	return (a1, m1)

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

# O(N^(1/4) * Log(N)).
def euler_phi(n):
	f = factor(n)
	ans = n

	for i in range(len(f)):
		ans //= f[i][0]
		ans *= (f[i][0] - 1)

	return ans

# O(N^(1/4) * Log(N)) - Returns the value of a^a^a^a^a... mod n
def power_tower(a, n):
	if n == 1:
		return 0

	cf = 1 # Common factors.
	g = gcd(a, n)

	# O(Log^2(N)).
	while g > 1:
		cf *= g
		n //= g
		g = gcd(a, n)

	# crt([0, a^f(phi(n))], [cf, n]).
	return chinese_remainder_theorem([0, pow(a, power_tower(a, euler_phi(n)), n)], [cf, n])[0]
