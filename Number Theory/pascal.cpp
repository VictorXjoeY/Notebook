#define MOD 1000000007
#define N 1000

long long nck[N + 2][N + 2];

void pascal(){
	int i, j;

	// Filling column 0 with 1.
	for (i = 0; i <= N; i++){
		nck[i][0] = 1;
	}

	// Calculating NCK(i, j).
	for (i = 1; i <= N; i++){
		for (j = 1; j <= i; j++){
			nck[i][j] = (nck[i - 1][j - 1] + nck[i - 1][j]) % MOD;
		}
	}
}