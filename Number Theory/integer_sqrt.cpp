// MAX is defined such that the binary search doesn't overflow the long long.
constexpr long long MAX = 3000000000ll;

/* O(min(Log(N), Log(MAX))) - Returns the greatest integer k such that k^2 <= n (n <= 9 * 10^18). */
long long integer_sqrt(long long n){
	long long l, r, m;

	l = 0;
	r = min(n, MAX);

	while (l < r){
		m = (l + r + 1) / 2;

		if (m * m <= n){
			l = m;
		}
		else{
			r = m - 1;
		}
	}

	return l;
}