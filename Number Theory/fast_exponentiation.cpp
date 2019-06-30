/* O(Log(Y)). */
long long fast_exp(long long x, long long y, long long m){
	long long ans = 1; // Base case.

	// In case x >= m.
	x %= m;

	// Decomposing y in binary. Multiplying the answer by x^1, x^2, x^4, x^8, ...
	while (y > 0){
		// If current bit is set.
		if (y & 1ll){
			ans = (ans * x) % m;
		}

		y >>= 1ll; // Next bit.
		x = (x * x) % m; // Next power of x.
	}

	return ans;
}