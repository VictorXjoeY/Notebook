N = 1000000

# mp[i] stores the minimum prime number which divides i. i is prime if it's not 0 and mp[i] == i.
mp = [0 for i in range(N + 1)]

# O(N) - Returns the prime numbers up to n.
def linear_sieve(n):
	p = [] # Stores prime numbers.

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

# O(Log(N)).
def factor(n):
	# Asserting that linear_sieve was executed before factorizing.
	assert(mp[2] == 2)

	# Retrieving exponents.
	f = []

	# While there are still prime factors.
	while n > 1:
		if len(f) > 0 and mp[n] == f[-1][0]:
			f[-1][1] += 1
		else:
			f.append([mp[n], 1])

		# Dividing n by its smallest prime factor.
		n //= mp[n]

	return f