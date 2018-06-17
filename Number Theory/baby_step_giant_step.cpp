/* O(log(y)). */
long long fast_exp(long long x, long long y, long long mod){
	long long ans = 1; // Base case.

	// Decomposing y in binary. Multiplying the answer by x^1, x^2, x^4, x^8, ...
	while (y > 0){
		// If current bit is set.
		if (y & 1ll){
			ans = (ans * x) % mod;
		}

		y >>= 1ll; // Next bit.
		x = (x * x) % mod; // Next power of x.
	}

	return ans;
}

/* O(sqrt(N)). Solves a^x = b (mod n) for a, b < n. */
/* Basic idea is to rewrite: x = m * q + r with m = sqrt(n) */
long long baby_step_giant_step(long long a, long long b, long long n){
	unordered_map<long long, long long> table;
	long long a_inv_m, m, r, q, cur;

	// Defining m as ceil(sqrt(n)).
	m = sqrt(n - 1) + 1;

	// Computing a^(-m).
	a_inv_m = fast_exp(fast_exp(a, n - 2, n), m, n);

	// Baby-step.
	for (r = 0, cur = 1; r < m; r++, cur = (cur * a) % n){
		table[cur] = r;
	}

	// Giant-step.
	for (q = 0, cur = 1; q < m; q++, cur = (cur * a_inv_m) % n){
		if (table.count((cur * b) % n)){
			return m * q + table[(cur * b) % n];
		}
	}

	// No solution.
	return -1;
}