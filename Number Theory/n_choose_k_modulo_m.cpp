// Reference: https://www.youtube.com/watch?v=DBR6eW3MuiU

vector<pair<long long, long long>> factor; // Vector of pairs (prime, prime^exponent)
vector<vector<long long>> dp_f; // dp for function f(n).

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

/* O(sqrt(N)). */
vector<pair<long long, long long>> factorization(long long n) {
	vector<pair<long long, long long>> f; // Sorted vector of pairs (prime, exponent).

	// For every prime p up to sqrt(n).
	for (long long p = 2; p * p <= n; p++) {
		if (n % p == 0) {
			f.push_back({p, 0ll});
			
			// While p divides n, keep dividing n by p and increasing the number of p factors.
			while (n % p == 0) {
				n /= p;
				f.back().second++;
			}
		}
	}

	// If n is not 1 by now, then it is a prime factor.
	if (n > 1) {
		f.push_back({n, 1ll});
	}
	
	return f;
}

/* O(LogP(N)) - Returns the number of prime factors p in n!. */
long long factorial_factorization(long long n, long long p) {
	long long ans, k;

	// Initializing.
	ans = 0;
	k = p;

	// While n / k still adds to the answer.
	while (k <= n) {
		ans += n / k;

		// Checking for overflow.
		if (k > 1000000000000000000LL/p) {
			break;
		}

		k *= p;
	}

	return ans;
}

/* O(Log(min(a, b))) - Returns a * b mod m without overflowing. 2 * (m - 1) must not overflow. */
long long mod_mul(long long a, long long b, long long m) {
	// O(1) - If there's __int128_t available, just multiply.
	#ifdef __SIZEOF_INT128__
		return ((__int128_t)a * (__int128_t)b) % m;
	#endif

	// In case a >= m or b >= m.
	a = (a % m + m) % m;
	b = (b % m + m) % m;

	// Forcing b to be the smallest.
	if (a < b) {
		swap(a, b);
	}

	long long ans = 0;

	// Decomposing b in binary. Adding to the answer a * 2^0, a * 2^1, a * 2^2, a * 2^4, a * 2^8, ...
	while (b > 0) {
		// If current bit is set.
		if (b & 1ll) {
			ans = (ans + a) % m;
		}

		b >>= 1ll; // Next bit.
		a = (2ll * a) % m; // Next power of two multiplied by a.
	}

	return ans;
}

/* O(Log(min(a, b))) - Extended Euclidean Algorithm.
   Returns a solution to a * x + b * y = gcd(a, b).
   Returns |x| <= |a / gcd(a, b)|, |y| <= |b / gcd(a, b)| and gcd(a, b). */
tuple<long long, long long, long long> extended_gcd(long long a, long long b) {
	long long x, y, gcd;

	if (a == 0) {
		return {b, 0, 1};
	}

	tie(gcd, x, y) = extended_gcd(b % a, a);

	return {gcd, y - (b / a) * x, x}; 
}

/* O(Log(min(a, b))).
a * x + b * y = c
	x = x1 + k * (b / gcd(a, b))
	y = y1 - k * (a / gcd(a, b))

a * x - b * y = c ---> a * x + b * (-y) = c
	x = x1 + k * (b / gcd(a, b))
	-y = y1 - k * (a / gcd(a, b)) ---> y = -y1 + k * (a / gcd(a, b))

-a * x + b * y = c ---> a * (-x) + b * y = c
	-x = x1 + k * (b / gcd(a, b)) ---> x = -x1 - k * (b / gcd(a, b))
	y = y1 - k * (a / gcd(a, b))

-a * x - b * y = c ---> a * (-x) + b * (-y) = c
	-x = x1 + k * (b / gcd(a, b)) ---> x = -x1 - k * (b / gcd(a, b))
	-y = y1 - k * (a / gcd(a, b)) ---> y = -y1 + k * (a / gcd(a, b))

Use positive values for a and b for this function.
Has infinite solutions if and only if gcd(a, b) divides c.
If a and/or b are 0, treat those cases separately.
Returns |x1| <= |(a * c) / gcd^2(a, b)|, |y1| <= |(b * c) / gcd^2(a, b)| and gcd(a, b) if there are solutions. */
tuple<long long, long long, long long> diophantine(long long a, long long b, long long c) {
	long long gcd, x, y;

	// Obtaining a * x1 + b * y1 = gcd(a, b)
	tie(gcd, x, y) = extended_gcd(a, b);

	// No solution
	if (c % gcd != 0) {
		return {0, 0, 0};
	}

	// Obtaining lcm(a, b).
	long long lcm = (a / gcd) * b;

	// Multiplying the above equation by k = c / gcd to obtain a * x1 + b * y1 = c
	return {gcd, mod_mul(x, (c / gcd), lcm), mod_mul(y, (c / gcd), lcm)};
}

/* O(N * Log(lcm(m1, m2, ..., mn))) - General Chinese Remainder Theorem.

Considering the following family of linear congruences:

t = a1 (mod m1)
t = a2 (mod m2)
...
t = an (mod mn)

Returns the smallest non-negative solution modulo lcm(m1, m2, ..., mn). Returns -1 if there is no solution.

The family of linear congruences has a solution if and only if every pair of linear congruences is consistent.
A pair of linear congruences is consistent if a1 = a2 (mod gcd(m1, m2)).

t = a1 (mod m1) ---> t - a1 = m1 * x
t = a2 (mod m2) ---> t - a2 = m2 * y

a1 + m1 * x = a2 + m2 * y
m1 * x - m2 * y = a2 - a1
m1 * x + m2 * (-y) = a2 - a1

x = x1 + k * m2 / gcd(m1, m2)
y = -y1 + k * m1 / gcd(m1, m2)

t - a1 = m1 * (x1 + k * m2 / gcd(m1, m2))
t - a1 = m1 * x1 + lcm(m1, m2) * k
t - (a1 + m1 * x1) = lcm(m1, m2) * k ---> t = a1 + m1 * x1 (mod lcm(m1, m2))

t - a2 = m2 * (-y1 + k * m1 / gcd(m1, m2))
t - a2 = -m2 * y1 + lcm(m1, m2) * k
t - (a2 - m2 * y1) = lcm(m1, m2) * k ---> t = a2 - m2 * y1 (mod lcm(m1, m2)) */
pair<long long, long long> chinese_remainder_theorem(vector<long long> a, vector<long long> m) {
	long long a1, m1, a2, m2, x1, y1, gcd, lcm;

	// Making 0 <= ai < mi.
	for (int i = 0; i < a.size(); i++) {
		a[i] = ((a[i] % m[i]) + m[i]) % m[i];
	}

	a1 = 0;
	m1 = 1;

	for (int i = 0; i < a.size(); i++) {
		a2 = a[i];
		m2 = m[i];

		// Solving m1 * x + m2 * (-y) = a2 - a1
		tie(gcd, x1, y1) = diophantine(m1, m2, a2 - a1);

		if (gcd == 0) { // No solution.
			return {-1, 0};
		}

		// Calculating lcm(m1, m2) without overflowing.
		lcm = (m1 / gcd) * m2;

		// Updating answer.
		a1 = ((a1 + mod_mul(m1, x1, lcm)) % lcm + lcm) % lcm;
		m1 = lcm;
	}

	return {a1, m1};
}

/* O(1) - Returns 1 if p divides n and n otherwise. */
long long g(long long n, long long p) {
	return n % p == 0 ? 1 : n;
}

/* O(E) - Returns the value of f(n). */
long long f(long long n, long long p, long long pe, const vector<long long> &dp) {
	return (fast_exp(dp[pe], n / pe, pe) * dp[n % pe]) % pe;
}

/* O(E * LogP(N)) - Returns the value of F(n). */
long long F(long long n, long long p, long long pe, const vector<long long> &dp) {
	long long ans;

	for (ans = 1; n > 0; n /= p) {
		ans = (ans * f(n, p, pe, dp)) % pe;
	}

	return ans;
}

/* O(E * LogP(N)) - Calculates n choose k modulo p^e. */
long long nck_mod_prime_power(long long n, long long k, long long p, long long e, long long pe, const vector<long long> &dp) {
	long long num, den, nck_pe;

	nck_pe = factorial_factorization(n, p) - factorial_factorization(k, p) - factorial_factorization(n - k, p);

	if (nck_pe >= e) {
		return 0;
	}

	// O(E * LogP(N)).
	num = (fast_exp(p, nck_pe, pe) * F(n, p, pe, dp)) % pe;
	den = (F(k, p, pe, dp) * F(n - k, p, pe, dp)) % pe;

	// O(E) - After we extracted the p factors and placed them in the numerator, we can multiply by the
	// denominator's multiplicative inverse modulo p^e, which is equal to den^(totient(pe) - 1).
	return (num * fast_exp(den, pe - pe / p - 1, pe)) % pe;
}

/* O(Log(N) * Log(M) + Log^2(M)) - Calculates n choose k modulo m for any m. */
long long nck(long long n, long long k, long long m) {
	long long p, e, pe, a1, r1;
	vector<long long> a, r;

	// Trivial case.
	if (k < 0 or k > n) {
		return 0;
	}

	// O(Log(N) * Log(M)) - Calculating n choose k modulo each prime power that composes m.
	for (int i = 0; i < factor.size(); i++) {
		p = factor[i].first;
		e = factor[i].second;
		pe = fast_exp(p, e, m + 1);
		a.push_back(nck_mod_prime_power(n, k, p, e, pe, dp_f[i]));
		r.push_back(pe); 
	}

	// O(Log^2(M)) - Composing the answer. Remember that r1 is just m.
	tie(a1, r1) = chinese_remainder_theorem(a, r);

	return a1;
}

/* O(P^E) - Pre-calculates the value of f(n) for n from 1 to p^e. */
vector<long long> f_init(long long p, long long pe) {
	vector<long long> dp;

	dp.resize(pe + 1);
	dp[0] = 1;

	for (int i = 1; i <= pe; i++) {
		dp[i] = (dp[i - 1] * g(i, p)) % pe;
	}

	return dp;
}

/* O(M) - Pre-calculates factors and function f(n) for a given modulo m. */
void nck_init(long long m) {
	long long p, e, pe;

	// O(sqrt(M)) - Returns the pairs (p, p^e) from the factorization of m.
	factor = factorization(m);
	dp_f.resize(factor.size());

	// O(M) - For each prime power that composes m.
	for (int i = 0; i < factor.size(); i++) {
		p = factor[i].first;
		e = factor[i].second;
		pe = fast_exp(p, e, m + 1);
		dp_f[i] = f_init(p, pe);
	}
}