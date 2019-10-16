# O(sqrt(N)).
def mobius(n):
	ans = 0
	p = 2

	# For every prime p up to sqrt(n).
	while p * p <= n:
		# If prime p divides n.
		if n % p == 0:
			# Not square-free.
			if n % (p * p) == 0:
				return 0

			ans += 1
			n //= p

		p += 1

	# If n is not 1 by now, then it is a prime factor.
	ans += (n > 1)

	return 1 if ans % 2 == 0 else -1
