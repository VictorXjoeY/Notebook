# O(min(Log(N), Log(MAX))) - Returns the greatest integer k such that k^2 <= n.
def integer_sqrt(n):
	l, r = 0, n

	while l < r:
		m = (l + r + 1) // 2

		if m * m <= n:
			l = m
		else:
			r = m - 1

	return l

# O(log(max(a, b))).
# a * x + b * y = gcd(a, b)
def extended_gcd(a, b):
	if a == 0:
		return (b, 0, 1)

	gcd, x, y = extended_gcd(b % a, a)

	return (gcd, y - (b // a) * x, x)

# O(Log(M)) - Returns the modular multiplicative inverse of a mod m, if it exists.
# Returns x that satisfies a * x = 1 (mod m) if a and m are coprime. Returns 0 otherwise.
def modular_inverse(a, m):
	g, x, y = extended_gcd((a % m + m) % m, m)

	if g != 1:
		return 0

	return (x % m + m) % m

# O(sqrt(N)) - Solves a^x = b (mod n) for 0 <= a, b < n. Returns -1 if there's no solution.
# If a and n are coprime then the basic idea is to rewrite: x = m * q + r with m = sqrt(n)
# If a and n are not coprime then we have gcd(a, n) = g > 1 and:
# a = g * alpha
# b = g * beta --- If b is not divisible by g then there's no solution.
# n = g * mu
# Reduce:
# (g * alpha)^x = g * beta (mod g * mu)
# By dividing it by g:
# (g * alpha)^(x - 1) = beta * alpha^(-1) (mod mu)
def baby_step_giant_step(a, b, n):
	g = extended_gcd(a, n)[0]

	if g > 1:
		# No solution
		if b % g != 0:
			return -1

		alpha = a // g
		beta = b // g
		mu = n // g

		x = baby_step_giant_step(a % mu, (beta * modular_inverse(alpha, mu)) % mu, mu)

		if x == -1:
			return -1

		return x + 1

	# Defining m as ceil(sqrt(n)).
	m = integer_sqrt(n)

	if m * m < n:
		m += 1

	# Computing a^(-m).
	a_inv_m = pow(modular_inverse(a, n), m, n)
	table = {}
	cur = 1

	# Baby-step.
	for r in range(m):
		table[cur] = r
		cur = (cur * a) % n

	cur = 1

	# Giant-step.
	for q in range(m):
		if (cur * b) % n in table:
			return m * q + table[(cur * b) % n]

		cur = (cur * a_inv_m) % n

	return -1