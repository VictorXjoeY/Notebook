/* O(LogP(N)) - Returns the number of prime factors p in n!. */
long long factorial_factorization(long long n, long long p){
	long long ans, k;

	// Initializing.
	ans = 0;
	k = p;

	// While n / k still adds to the answer.
	while (k <= n){
		ans += n / k;
		k *= p;
	}

	return ans;
}
