# O(1).
def ceil(num, den):
	return (num + den - 1) // den

# O(log(max(a, b))).
# a * x + b * y = gcd(a, b)
def extended_gcd(a, b):
	if a == 0:
		return (b, 0, 1)

	gcd, x, y = extended_gcd(b % a, a)

	return (gcd, y - (b // a) * x, x)

# O(log(max(a, b))).
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
	gcd, x1, y1 = extended_gcd(a, b)

	# No solution
	if c % gcd != 0:
		return (0, 0, 0)

	# Multiplying the above equation by k = c / gcd to obtain a * x1 + b * y1 = c
	x1 *= c // gcd
	y1 *= c // gcd

	# Simplifying the solution so that x1 is minimum and positive. Use positive values for a and b for this to work as intended!
	k = ceil(-x1 * gcd, b)
	x1 += k * (b // gcd)
	y1 -= k * (a // gcd)

	return (gcd, x1, y1)

# O(N * log(lcm(m1, m2, ..., mn))) - General Chinese Remainder Theorem.
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

	a1 = a[0]
	m1 = m[0]

	for i in range(1, len(a)):
		a2 = a[i]
		m2 = m[i]

		# Solving m1 * x + m2 * (-y) = a2 - a1
		gcd, x1, y1 = diophantine(m1, m2, a2 - a1)

		if gcd == 0: # No solution.
			return (-1, 0)

		# Calculating lcm(m1, m2).
		lcm = (m1 * m2) // gcd

		# Updating answer.
		a1 = (a1 + m1 * x1) % lcm
		m1 = lcm

	return (a1, m1)

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

# O(sqrt(N)) - Returns the value of a^a^a^a^a... mod n
def power_tower(a, n):
	if n == 1:
		return 0

	cf = 1 # Common factors.
	g = extended_gcd(a, n)[0]

	while g > 1:
		cf *= g
		n //= g
		g = extended_gcd(a, n)[0]

	if n == 1:
		return 0

	# crt([0, a^f(x + 1)], [cf, n]) such that a^x = a^(-1) (mod n)
	return chinese_remainder_theorem([0, pow(a, power_tower(a, baby_step_giant_step(a % n, modular_inverse(a, n), n) + 1), n)], [cf, n])[0]