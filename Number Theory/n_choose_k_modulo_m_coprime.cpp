#define N 1000000

long long f[N + 1];

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

/* O(Log(M)) - This only works if k! * (n - k)! is coprime with m. */
long long nck(long long n, long long k, long long m){
	long long num, den;

	// Trivial case.
	if (k < 0 or k > n){
		return 0;
	}

	num = f[n];
	den = (f[k] * f[n - k]) % m;

	return (num * fast_exp(den, m - 2, m)) % m;
}

/* O(N). */
void nck_init(long long m){
	f[0] = 1;

	for (long long i = 1; i <= N; i++){
		f[i] = (f[i - 1] * i) % m;
	}
}