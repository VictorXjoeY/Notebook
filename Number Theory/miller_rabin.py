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