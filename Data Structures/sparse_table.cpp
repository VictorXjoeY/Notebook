#define N 100000
#define L 20

int table[N + 1][L + 1];
int a[N + 1]; // (Input)
int n; // (Input)

/* O(1) - Idempotent operation. */
int merge(int x, int y){
	return max(x, y);
}

/* O(N * Log(N)). */
void build(){
	int i, j;

	// Base.
	for (i = 1; i <= n; i++){
		table[i][0] = a[i];
	}

	// Building for each 2^j <= n
	for (j = 1; (1 << j) <= n; j++){
		// Building for each [i, i + 2^j - 1]
		for (i = 1; i + (1 << j) - 1 <= n; i++){
			table[i][j] = merge(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
		}
	}
}

/* O(1). */
int query(int l, int r){
	int k;

	// Finding greatest k such that 2^k <= r - l + 1
	k = 32 - __builtin_clz(r - l + 1) - 1;

	return merge(table[l][k], table[r - ((1 << k) - 1)][k]);
}