#define MOD 1000000007

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