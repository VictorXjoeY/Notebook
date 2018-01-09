#define N 1000000

int f[N + 1];

/* O(sqrt(N)). */
void factorization(int n){
	// For every i up to sqrt(n).
	for (i = 2; i * i <= n; i++){
		// While i divides n, keep dividing n by i and increasing the number of i factors. i is a prime.
		while (n % i == 0){
			n /= i;
			f[i]++;
		}
	}

	// If n is not 1 by now, then it is a prime.
	if (n > 1){
		f[n]++;
	}
}
