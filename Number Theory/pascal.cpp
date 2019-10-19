constexpr int MOD = 1000000007;
constexpr int N = 1000;

long long nck[N + 2][N + 2];

/* O(N^2). */
void pascal() {
	// Filling column 0 with 1.
	for (int i = 0; i <= N; i++) {
		nck[i][0] = 1;
	}

	// Calculating NCK(i, j).
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= i; j++) {
			nck[i][j] = (nck[i - 1][j - 1] + nck[i - 1][j]) % MOD;
		}
	}
}