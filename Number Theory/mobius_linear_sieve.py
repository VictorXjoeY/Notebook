N = 1000000

# mp[i] stores the minimum prime number which divides i. i is prime if it's not 0 and mp[i] == i.
mp = [0 for i in range(N + 1)]
mobius = [0 for i in range(N + 1)]

# O(N) - Returns the prime numbers up to n.
def linear_sieve(n):
	p = [] # Stores prime numbers.
	mobius[1] = 1

	for i in range(2, n + 1):
		if mp[i] == 0: # i is prime if we haven't found any smaller factors of it.
			mobius[i] = -1
			mp[i] = i
			p.append(i)
		
		# Since every number x can be written as x = i * mp[x] we can iterate over every prime mp[x] (prime[j]).
		j = 0

		while j < len(p) and p[j] <= mp[i] and i * p[j] <= n:
			# mobius[x] = mobius[i * mp[x]] = mobius[i] * 0 if mp[x] divides i or mobius[i] * -1 if mp[x] doesn't divide i.
			mobius[i * p[j]] = mobius[i] * (0 if p[j] == mp[i] else -1)
			mp[i * p[j]] = p[j]
			j += 1

	return p
