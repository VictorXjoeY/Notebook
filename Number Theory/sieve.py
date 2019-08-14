# O(N) - Returns the prime numbers up to n.
def sieve(n):
	# Initializing.
	prime = [True for i in range(n + 1)]
	prime[0] = prime[1] = False
	p = []

	# For every number i up to sqrt(N).
	for i in range(2, n + 1):
		# If current number is prime.
		if prime[i]:
			p.append(i) # Appending prime.

			# Marking its multiples to not prime.
			j = i * i

			while j <= n:
				prime[j] = False
				j += i

	return p