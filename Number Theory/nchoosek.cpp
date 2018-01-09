#define MOD 1000000007
#define N 1000000

long long f[N + 1];

/* O(log(y)). */
long long fast_exp(long long x, long long y){
	long long ans;

	// Base case.
	if (y == 0){
		return 1;
	}

	// x^y = x^(y / 2) * x^(y / 2).
	ans = fast_exp(x, y / 2);
	ans = (ans * ans) % MOD;

	// Adjusting in case exponent is odd.
	if (y % 2){
		ans = (ans * x) % MOD;
	}

	return ans;
}

/* O(log(MOD)). */
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