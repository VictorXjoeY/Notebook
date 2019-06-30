#define N 1000000

bool prime[N + 1];
vector<int> p;

/* O(N * Log(Log(N))). */
void sieve(){
	// Initializing.
	memset(prime, true, sizeof(prime));
	prime[0] = prime[1] = false;

	// For every number i up to sqrt(N). */
	for (int i = 2; i <= N; i++){
		// If current number is prime.
		if (prime[i]){
			// Pushing the primes into an array.
			p.push_back(i);

			// Marking its multiples to not prime.
			for (int j = i * i; j <= N; j += i){
				prime[j] = false;
			}
		}
	}
}