long long fast_exp(long long x, long long y){
	long long ans;

	if (y == 0){
		return 1;
	}

	ans = fast_exp(x, y / 2);
	ans = (ans * ans) % MOD;

	if (y % 2){
		ans = (ans * x) % MOD;
	}

	return ans;
}

long long nck(long long n, long long k){
	long long num, den, i;

	for (i = n, num = 1; i > n - k; i--){
		num = (num * i) % MOD;
	}

	for (i = 1, den = 1; i <= k; i++){
		den = (den * i) % MOD;
	}

	return (num * fast_exp(den, MOD - 2)) % MOD;
}