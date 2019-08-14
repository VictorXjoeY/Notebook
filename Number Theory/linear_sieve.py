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