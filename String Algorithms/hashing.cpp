#define N 100000

long long mod[2] = {1000000007, 1000000009};
long long prime[2] = {31, 37};
long long pot[2][N + 1];
long long s[2][N + 1];
char str[N + 2];
int n;

/* O(1) - Retrieves a pair of hashes representing the range [l, r]. */
pair<long long, long long> range_hash(int l, int r){
	long long h[2];
	int k;

	for (k = 0; k < 2; k++){
		h[k] = (((s[k][r] - s[k][l - 1] + mod[k]) % mod[k]) * pot[k][n - r]) % mod[k];
	}

	return make_pair(h[0], h[1]);
}

/* O(N) - Calculates the prime powers and the accumulated hash function. */
void initialize(){
	int i, k;

	// O(N) - Calculating powers.
	for (k = 0; k < 2; k++){
		pot[k][0] = 1;

		for (i = 1; i <= n; i++){
			pot[k][i] = (pot[k][i - 1] * prime[k]) % mod[k];
		}
	}

	// O(N) - Remapping the string to the range [0, 26].
	for (i = 1; i <= n; i++){
		str[i] -= 'a';
	}

	// O(N) - Calculating the accumulated hash function.
	for (k = 0; k < 2; k++){
		for (i = 1; i <= n; i++){
			s[k][i] = (s[k][i - 1] + str[i] * pot[k][i]) % mod[k];
		}
	}
}