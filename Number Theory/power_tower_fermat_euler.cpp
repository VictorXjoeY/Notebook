mt19937_64 rng_64(chrono::steady_clock::now().time_since_epoch().count());

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

/* O(Log(B)). */
long long fast_exp(long long a, long long b, long long m) {
	long long ans = 1; // Base case.

	// In case a >= m.
	a %= m;

	// Decomposing b in binary. Multiplying the answer by a^1, a^2, a^4, a^8, ...
	while (b > 0) {
		// If current bit is set.
		if (b & 1ll) {
			ans = mod_mul(ans, a, m);
		}

		b >>= 1ll; // Next bit.
		a = mod_mul(a, a, m); // Next power of a.
	}

	return ans;
}

/* O(Log(N)) - Returns true if n is probably prime and returns false if it composite for sure. */
bool is_probably_prime(long long n, long long a, long long d, int s) {
	long long x = fast_exp(a, d, n);

	// a^d = 1 (mod n)
	if (x == 1) {
		return true;
	}

	// a^(d * 2^r) = -1 (mod n), 0 <= r < s
	for (int r = 0; r < s; r++) {
		if (x == n - 1) {
			return true;
		}

		x = mod_mul(x, x, n);
	}

	return false;
}

/* O(12 * Log(N)) - Deterministic Miller Rabin for 64 bit integers. Returns true if n is prime and returns false otherwise. */
bool miller_rabin(long long n) {
	long long a[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

	if (n <= 1) {
		return false;
	}

	// O(Log(N) - Decomposing n - 1 = d * 2^s
	int s = 0;
	long long d = n - 1;

	while (d % 2 == 0) {
		d /= 2;
		s++;
	}

	// For each prime base a[i].
	for (int i = 0; i < 12; i++) {
		if (n == a[i]) {
			return true;
		}

		if (!is_probably_prime(n, a[i], d, s)) {
			return false;
		}
	}

	return true;
}

/* O(1) - Returns f(x) = x^2 + c. */
long long f(long long x, long long c, long long n) {
	return (mod_mul(x, x, n) + c) % n;
}

/* O(N^(1/4) * Log(N)) - Finds a divisor 1 < d < n of n. Expects a composite number. */
long long pollard_rho(long long n) {
	if (n % 2 == 0) {
		return 2;
	}

	// Randomizing values for x0 and c for the polynomial f(x) = x^2 + c.
	long long tortoise = uniform_int_distribution<long long>(2, n - 1)(rng_64);
	long long hare = tortoise;
	long long c = uniform_int_distribution<long long>(1, n - 1)(rng_64);
	long long g = 1;

	while (g == 1) {
		tortoise = f(tortoise, c, n);
		hare = f(f(hare, c, n), c, n);
		g = __gcd(abs(hare - tortoise), n);
	}

	// Failed to find a divisor. Trying again.
	if (g == n) {
		return pollard_rho(n);
	}

	// Found a divisor.
	return g;
}

/* O(N^(1/4) * Log(N)). */
void factorization(long long n, vector<long long> &p) {
	// No prime factors.
	if (n == 1) {
		return;
	}

	// Prime.
	if (miller_rabin(n)) {
		p.push_back(n);
		return;
	}

	// Composite.
	long long d = pollard_rho(n);
	factorization(d, p);
	factorization(n / d, p);
}

/* O(N^(1/4) * Log(N)). */
vector<pair<long long, long long>> factor(long long n) {
	vector<pair<long long, long long>> f; // Sorted vector of pairs (prime, exponent).
	vector<long long> p; // Vector of prime factors.

	// Factorizing.
	factorization(n, p);
	sort(p.begin(), p.end());

	// Retrieving exponents.
	for (int i = 0; i < p.size(); i++) {
		if (!f.empty() and p[i] == f.back().first) {
			f.back().second++;
		}
		else{
			f.push_back({p[i], 1ll});
		}
	}

	return f;
}

/* O(N^(1/4) * Log(N)). */
long long euler_phi(long long n) {
	vector<pair<long long, long long>> f = factor(n);
	long long ans = n;

	// For every prime factor of n.
	for (int i = 0; i < f.size(); i++) {
		ans /= f[i].first;
		ans *= (f[i].first - 1);
	}

	return ans;
}

/* O(N^(1/4) * Log(N)) - Returns the value of a^a^a^a^a... mod n */
long long power_tower(long long a, long long n) {
	if (n == 1) {
		return 0;
	}

	long long cf = 1; // Common factors.
	long long g = __gcd(a, n);

	// O(Log^2(N)).
	while (g > 1) {
		cf *= g;
		n /= g;
		g = __gcd(a, n);
	}
	
	// crt([0, a^f(phi(n))], [cf, n]).
	long long a1, m1;
	vector<long long> r = {0ll, fast_exp(a, power_tower(a, euler_phi(n)), n)};
	vector<long long> m = {cf, n};
	tie(a1, m1) = chinese_remainder_theorem(r, m);

	return a1;
}