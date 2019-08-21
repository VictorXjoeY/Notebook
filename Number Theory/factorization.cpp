/* O(sqrt(N)). */
vector<pair<long long, long long>> factorization(long long n){
	vector<pair<long long, long long>> f; // Sorted vector of pairs (prime, exponent).

	// For every prime p up to sqrt(n).
	for (long long p = 2; p * p <= n; p++){
		if (n % p == 0){
			f.push_back({p, 0ll});
			
			// While p divides n, keep dividing n by p and increasing the number of p factors.
			while (n % p == 0){
				n /= p;
				f.back().second++;
			}
		}
	}

	// If n is not 1 by now, then it is a prime factor.
	if (n > 1){
		f.push_back({n, 1ll});
	}
	
	return f;
}
