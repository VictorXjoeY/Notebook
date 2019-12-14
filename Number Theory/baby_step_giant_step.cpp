// MAX is defined such that the binary search doesn't overflow the long long.
constexpr long long MAX = 3000000000ll;

/* O(min(Log(N), Log(MAX))) - Returns the greatest integer k such that k^2 <= n (n <= 9 * 10^18). */
long long integer_sqrt(long long n) {
	long long l, r, m;

	l = 0;
	r = min(n, MAX);

	while (l < r) {
		m = (l + r + 1) / 2;

		if (m * m <= n) {
			l = m;
		}
		else{
			r = m - 1;
		}
	}

	return l;
}

/* O(Log(B)). */
long long fast_exp(long long a, long long b, long long m) {
	long long ans = 1; // Base case.

	// In case a >= m.
	a %= m;

	// Decomposing b in binary. Multiplying the answer by a^1, a^2, a^4, a^8, ...
	while (b > 0) {
		// If current bit is set.
		if (b & 1ll) {
			ans = (ans * a) % m;
		}

		b >>= 1ll; // Next bit.
		a = (a * a) % m; // Next power of a.
	}

	return ans;
}

/* O(Log(min(a, b))). */
/* a * x + b * y = gcd(a, b) */
long long extended_gcd(long long a, long long b, long long &x, long long &y) {
	long long x1, y1, gcd;

	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}
 
	gcd = extended_gcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
 
	return gcd;
}

/* O(Log(M)) - Returns the modular multiplicative inverse of a mod m, if it exists.
Returns x that satisfies a * x = 1 (mod m) if a and m are coprime. Returns 0 otherwise. */
long long modular_inverse(long long a, long long m) {
	long long x, y;

	if (extended_gcd((a % m + m) % m, m, x, y) != 1) {
		return 0;
	}

	return (x % m + m) % m;
}

/* O(sqrt(N)) - Solves a^x = b (mod n) for 0 <= a, b < n. Returns -1 if there's no solution.
If a and n are coprime then the basic idea is to rewrite: x = m * q + r with m = sqrt(n)
If a and n are not coprime then we have gcd(a, n) = g > 1 and:
a = g * alpha
b = g * beta --- If b is not divisible by g then there's no solution.
n = g * mu
Reduce:
(g * alpha)^x = g * beta (mod g * mu)
By dividing it by g:
(g * alpha)^(x - 1) = beta * alpha^(-1) (mod mu) */
long long baby_step_giant_step(long long a, long long b, long long n) {
	unordered_map<long long, long long> table;

	long long g = __gcd(a, n);

	if (g > 1) {
		// No solution.
		if (b % g != 0) {
			return -1;
		}

		long long alpha = a / g;
		long long beta = b / g;
		long long mu = n / g;

		long long x = baby_step_giant_step(a % mu, (beta * modular_inverse(alpha, mu)) % mu, mu);

		if (x == -1) {
			return -1;
		}

		return x + 1;
	}

	// Defining m as ceil(sqrt(n)).
	long long m = integer_sqrt(n);

	if (m * m < n) {
		m++;
	}

	// Computing a^(-m).
	long long a_inv_m = fast_exp(modular_inverse(a, n), m, n);

	// Baby-step.
	for (long long r = 0, cur = 1; r < m; r++, cur = (cur * a) % n) {
		table[cur] = r;
	}

	// Giant-step.
	for (long long q = 0, cur = 1; q < m; q++, cur = (cur * a_inv_m) % n) {
		if (table.count((cur * b) % n)) {
			return m * q + table[(cur * b) % n];
		}
	}

	// No solution.
	return -1;
}