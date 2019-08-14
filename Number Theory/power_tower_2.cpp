// MAX is defined such that the binary search doesn't overflow the long long.
#define MAX 3000000000ll

long long ceil(long long, long long);

/* O(1) - Integer division num / den that behaves like Python so that you can properly deal with inequations like x >= a / b. */
long long floor(long long num, long long den){
	if ((num >= 0 and den >= 0) or (num < 0 and den < 0)){
		return abs(num) / abs(den);
	}

	return -ceil(abs(num), abs(den));
}

/* O(1). */
long long ceil(long long num, long long den){
	return floor(num + den - 1, den);
}

/* O(Log(B)). */
long long fast_exp(long long a, long long b, long long m){
	long long ans = 1; // Base case.

	// In case a >= m.
	a %= m;

	// Decomposing b in binary. Multiplying the answer by a^1, a^2, a^4, a^8, ...
	while (b > 0){
		// If current bit is set.
		if (b & 1ll){
			ans = (ans * a) % m;
		}

		b >>= 1ll; // Next bit.
		a = (a * a) % m; // Next power of a.
	}

	return ans;
}

/* O(Log(max(a, b))). */
/* a * x + b * y = gcd(a, b) */
long long extended_gcd(long long a, long long b, long long &x, long long &y){
	long long x1, y1, gcd;

	if (a == 0){
		x = 0;
		y = 1;
		return b;
	}
 
	gcd = extended_gcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
 
	return gcd;
}

/* O(Log(max(a, b))).
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
If a and/or b are 0, treat those cases separately. */
long long diophantine(long long a, long long b, long long c, long long &x1, long long &y1){
	long long gcd, k;

	// Obtaining a * x1 + b * y1 = gcd(a, b)
	gcd = extended_gcd(a, b, x1, y1);

	// No solution
	if (c % gcd != 0){
		return 0;
	}

	// Multiplying the above equation by k = c / gcd to obtain a * x1 + b * y1 = c
	x1 *= c / gcd;
	y1 *= c / gcd;

	// Simplifying the solution so that x1 is minimum and positive. Use positive values for a and b for this to work as intended!
	k = ceil(-x1 * gcd, b);
	x1 += k * (b / gcd);
	y1 -= k * (a / gcd);

	return gcd;
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
void chinese_remainder_theorem(vector<long long> a, vector<long long> m, long long &a1, long long &m1){
	long long a2, m2, x1, y1, gcd, lcm;

	// Making 0 <= ai < mi.
	for (int i = 0; i < (int)a.size(); i++){
		a[i] = ((a[i] % m[i]) + m[i]) % m[i];
	}

	a1 = a[0];
	m1 = m[0];

	for (int i = 1; i < (int)a.size(); i++){
		a2 = a[i];
		m2 = m[i];

		// Solving m1 * x + m2 * (-y) = a2 - a1
		gcd = diophantine(m1, m2, a2 - a1, x1, y1);

		if (gcd == 0){ // No solution.
			a1 = -1;
			m1 = 0;
			return;
		}

		// Calculating lcm(m1, m2) without overflowing.
		lcm = (m1 / gcd) * m2;

		// Updating answer.
		a1 = (a1 + m1 * x1) % lcm;
		m1 = lcm;
	}
}

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

/* O(Log(M)) - Returns the modular multiplicative inverse of a mod m, if it exists.
Returns x that satisfies a * x = 1 (mod m) if a and m are coprime. Returns 0 otherwise. */
long long modular_inverse(long long a, long long m){
	long long x, y;

	if (extended_gcd((a % m + m) % m, m, x, y) != 1){
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
long long baby_step_giant_step(long long a, long long b, long long n){
	unordered_map<long long, long long> table;

	long long g = __gcd(a, n);

	if (g > 1){
		// No solution.
		if (b % g != 0){
			return -1;
		}

		long long alpha = a / g;
		long long beta = b / g;
		long long mu = n / g;

		long long x = baby_step_giant_step(a % mu, (beta * modular_inverse(alpha, mu)) % mu, mu);

		if (x == -1){
			return -1;
		}

		return x + 1;
	}

	// Defining m as ceil(sqrt(n)).
	long long m = integer_sqrt(n);

	if (m * m < n){
		m++;
	}

	// Computing a^(-m).
	long long a_inv_m = fast_exp(modular_inverse(a, n), m, n);

	// Baby-step.
	for (long long r = 0, cur = 1; r < m; r++, cur = (cur * a) % n){
		table[cur] = r;
	}

	// Giant-step.
	for (long long q = 0, cur = 1; q < m; q++, cur = (cur * a_inv_m) % n){
		if (table.count((cur * b) % n)){
			return m * q + table[(cur * b) % n];
		}
	}

	// No solution.
	return -1;
}

/* O(sqrt(N)) - Returns the value of a^a^a^a^a... mod n */
long long power_tower(long long a, long long n){
	if (n == 1){
		return 0;
	}

	long long cf = 1; // Common factors.
	long long g = __gcd(a, n);

	// O(Log^2(N)).
	while (g > 1){
		cf *= g;
		n /= g;
		g = __gcd(a, n);
	}

	if (n == 1){
		return 0;
	}

	// crt([0, a^f(x + 1)], [cf, n]) such that a^x = a^(-1) (mod n)
	long long a1, m1;
	vector<long long> r = {0ll, fast_exp(a, power_tower(a, baby_step_giant_step(a % n, modular_inverse(a, n), n) + 1), n)};
	vector<long long> m = {cf, n};
	chinese_remainder_theorem(r, m, a1, m1);

	return a1;
}