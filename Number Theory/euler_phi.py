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