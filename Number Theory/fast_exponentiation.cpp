long long fast_exp(long long x, long long y){
	long long ans;

	if (y == 0){
		return 1;
	}

	ans = fast_exp(x, y / 2);
	ans = ans * ans;

	if (y % 2){
		ans = ans * x;
	}

	return ans;
}