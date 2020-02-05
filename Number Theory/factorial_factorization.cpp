/* O(LogP(N)) - Returns the number of prime factors p in n!. */
long long factorial_factorization(long long n, long long p) {
	long long ans, k;

	// Initializing.
	ans = 0;
	k = p;

	// While n / k still adds to the answer.
	while (k <= n) {
		ans += n / k;

		// Checking for overflow.
		if (k > numeric_limits<long long>::max() / p) {
			break;
		}

		k *= p;
	}

	return ans;
}
