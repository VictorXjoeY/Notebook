#define N 100000

long long a[N + 1];
long long m[N + 1];
int n;

/* O(log(max(a, b))). */
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

/* O(log(max(a, b))).
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
    
Has a solution if and only if gcd(a, b) divides c. GCD will be positive if a and b are positive. */
long long diophantine(long long a, long long b, long long c, long long &x1, long long &y1){
    long long gcd, k, t;

    // Obtaining a * x1 + b * y1 = gcd(a, b)
    gcd = extended_gcd(a, b, x1, y1);

    // No solution
    if (c % gcd != 0){
        return 0;
    }

    // Multiplying the above equation by k = c / gcd we have a * x1 + b * y1 = c
    k = c / gcd;
    x1 *= k;
    y1 *= k;

    // Simplifying the solution so that x1 is minimum and positive
    t = x1 / (b / gcd);
    x1 -= t * (b / gcd);
    y1 += t * (a / gcd);

    if (x1 < 0){
        t = x1 - (b / gcd) > 0 ? 1 : -1;
        x1 -= t * (b / gcd);
        y1 += t * (a / gcd);
    }

    return gcd;
}

/* O(N * log(lcm(m1, m2, ..., mn))).

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
void linear_congruences_system(long long &a1, long long &m1){
	long long a2, m2, x1, y1, gcd, lcm;
	int i;

	// Making 0 <= ai < mi.
	for (i = 1; i <= n; i++){
		a[i] = ((a[i] % m[i]) + m[i]) % m[i];
	}

	a1 = a[1];
	m1 = m[1];

	for (i = 2; i <= n; i++){
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