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

# O(sqrt(N))
def euler_phi(n):
	ans = n
	p = 2

	# For every prime p up to sqrt(n).
	while p * p <= n:
		# If prime p divides n.
		if n % p == 0:
			ans //= p
			ans *= (p - 1)

			# Removing every p factor.
			while n % p == 0:
				n //= p

		p += 1

	# If n is not 1 by now, then it is a prime factor.
	if n > 1:
		ans //= n
		ans *= (n - 1)

	return ans

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

	# crt([0, a^f(phi(n))], [cf, n]).
	return chinese_remainder_theorem([0, pow(a, power_tower(a, euler_phi(n)), n)], [cf, n])[0]