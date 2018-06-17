#define MOD 1000000007

/* O(log(y)). */
long long fast_exp(long long x, long long y){
	long long ans = 1; // Base case.

	// Decomposing y in binary. Multiplying the answer by x^1, x^2, x^4, x^8, ...
	while (y > 0){
		// If current bit is set.
		if (y & 1ll){
			ans = (ans * x) % MOD;
		}

		y >>= 1ll; // Next bit.
		x = (x * x) % MOD; // Next power of x.
	}

	return ans;
}