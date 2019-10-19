constexpr int OFFSET = 'a';
constexpr int N = 100000;
constexpr long long m[2] = {1000000007, 1000000009};
constexpr long long prime[2] = {31, 37}; // Choose primes greater than the size of the alphabet.

long long pot[2][N + 1];
long long s[2][N + 1];
char str[N + 2]; // (Input)
int n; // (Input)

/* O(1) - Retrieves a pair of hashes representing the range [l, r]. */
pair<long long, long long> range_hash(int l, int r){
	long long h[2];

	for (int k = 0; k < 2; k++){
		h[k] = (((s[k][r] - s[k][l - 1] + m[k]) % m[k]) * pot[k][n - r]) % m[k];
	}

	return {h[0], h[1]};
}

/* O(|S|) - Calculates the prime powers and the accumulated hash function. */
void initialize(){
	// O(|S|) - Calculating powers.
	for (int k = 0; k < 2; k++){
		pot[k][0] = 1;

		for (int i = 1; i <= n; i++){
			pot[k][i] = (pot[k][i - 1] * prime[k]) % m[k];
		}
	}

	// O(|S|) - Remapping the string to the range [0, 26].
	for (int i = 1; i <= n; i++){
		str[i] -= OFFSET;
	}

	// O(|S|) - Calculating the accumulated hash function.
	for (int k = 0; k < 2; k++){
		for (int i = 1; i <= n; i++){
			s[k][i] = (s[k][i - 1] + str[i] * pot[k][i]) % m[k];
		}
	}
}