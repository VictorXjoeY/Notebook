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