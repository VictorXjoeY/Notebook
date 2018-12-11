#define MOD 1000000007
#define N 1000000

long long f[N + 1];

/* O(Log(Y)). */
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

/* O(Log(MOD)). */
long long nck(long long n, long long k){
	long long num, den;

	if (k < 0 or k > n){
		return 0;
	}

	num = f[n];
	den = (f[k] * f[n - k]) % MOD;

	return (num * fast_exp(den, MOD - 2)) % MOD;
}

/* O(N). */
void nck_init(){
	long long i;

	f[0] = 1;

	for (i = 1; i <= N; i++){
		f[i] = (f[i - 1] * i) % MOD;
	}
}