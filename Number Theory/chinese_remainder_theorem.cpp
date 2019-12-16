long long ceil(long long, long long);

/* O(1) - Integer division num / den that behaves like Python so that you can properly deal with inequations like x >= a / b. */
long long floor(long long num, long long den) {
	if ((num >= 0 and den >= 0) or (num < 0 and den < 0)) {
		return abs(num) / abs(den);
	}

	return -ceil(abs(num), abs(den));
}

/* O(1). */
long long ceil(long long num, long long den) {
	return floor(num + den - 1, den);
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
If a and/or b are 0, treat those cases separately. */
long long diophantine(long long a, long long b, long long c, long long &x1, long long &y1) {
	long long gcd, k;

	// Obtaining a * x1 + b * y1 = gcd(a, b)
	gcd = extended_gcd(a, b, x1, y1);

	// No solution
	if (c % gcd != 0) {
		return 0;
	}

	// Multiplying the above equation by k = c / gcd to obtain a * x1 + b * y1 = c
	x1 *= c / gcd;
	y1 *= c / gcd;

	// Simplifying the solution so that x1 is minimum and non-negative. Use positive values for a and b for this to work as intended!
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
void chinese_remainder_theorem(vector<long long> a, vector<long long> m, long long &a1, long long &m1) {
	long long a2, m2, x1, y1, gcd, lcm;

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
		gcd = diophantine(m1, m2, a2 - a1, x1, y1);

		if (gcd == 0) { // No solution.
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