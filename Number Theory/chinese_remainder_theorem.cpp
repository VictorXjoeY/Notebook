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

/* O(log(max(a, b))). */
/* a * x1 + b * y1 = c */
/* x = x1 - t * (b / gcd(a, b)) */
/* y = y1 + t * (a / gcd(a, b)) */
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

/* O(N * Log(N)). */
long long chinese_remainder_theorem(){
	long long x, mod, a1, a2, m1, m2, x1, x2;
	int i;

	// Initializing answer and modulo.
	x = a[1] % m[1];
	mod = m[1];

	for (i = 2; i <= n; i++){
		// Considering the congruences:
		// x = a1 (mod m1)
		// x = a2 (mod m2)
		a1 = x;
		m1 = mod;
		a2 = a[i] % m[i];
		m2 = m[i];

		if (diophantine(m1, m2, 1, x1, x2) != 1){
			// Moduli are not pairwise coprime.
			assert(false);
		}

		// Updating modulo.
		mod *= m[i];

		// Calculating x = a1 * m2 * x2 + a2 * m1 * x1
		x = (((((a1 * m2) % mod) * x2) % mod + (((a2 * m1) % mod) * x1) % mod) % mod + mod) % mod;
	}

	return x;
}