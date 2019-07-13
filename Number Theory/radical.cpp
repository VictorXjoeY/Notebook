// MAX is defined such that the binary search doesn't overflow the long long.
#define MAX 3000000000ll

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

/* O(N^(1/3)) - Returns the product of the distinct prime numbers that divide n. */
long long radical(long long n){
	long long ans, p;

	ans = 1;

	// O(N^(1/3)) - For every prime p <= n^(1/3) that divides n.
	for (p = 2; p * p * p <= n; p++){
		if (n % p == 0){
			ans *= p;

			while (n % p == 0){
				n /= p;
			}
		}
	}

	// n is now either 1, p, p^2 or p1 * p2. If n is p^2 then we multiply
	// the answer by p, otherwise we multiply the answer by n.
	p = integer_sqrt(n);

	if (p * p == n){
		ans *= p;
	}
	else{
		ans *= n;
	}

	return ans;
}