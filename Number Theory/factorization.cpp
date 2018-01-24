#define N 1000000

int f[N + 1];

/* O(sqrt(N)). */
void factorization(int n){
	int p;

	// For every prime p up to sqrt(n).
	for (p = 2; p * p <= n; p++){
		// While p divides n, keep dividing n by p and increasing the number of p factors.
		while (n % p == 0){
			n /= p;
			f[p]++;
		}
	}

	// If n is not 1 by now, then it is a prime factor.
	if (n > 1){
		f[n]++;
	}
}
