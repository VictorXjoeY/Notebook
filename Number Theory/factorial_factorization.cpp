long long factorial_factorization(long long n, long long p){
	long long ans, k;

	ans = 0;
	k = p;

	while (true){
		if (n / k){
			ans += n / k;
			k *= p;
		}
		else{
			return ans;
		}
	}

	return 0;
}