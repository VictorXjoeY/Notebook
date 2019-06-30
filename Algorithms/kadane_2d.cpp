#define N 300

int mat[N + 1][N + 1]; // (Input)
int sum[N + 1][N + 1];
int dp[N + 1];
int n, m; // (Input)

int query(int y, int xi, int xf){
	return sum[y][xf] - sum[y][xi - 1];
}

/* O(N^3). */
int kadane_2d(){
	// Cumulative sum of each column j.
	for (int j = 1; j <= m; j++){
		for (int i = 1; i <= n; i++){
			sum[j][i] = sum[j][i - 1] + mat[i][j];
		}
	}

	// Initializing final answer.
	int ans = mat[1][1];

	// For each pair (xi, xf), run kadane on columns.
	for (int xi = 1; xi <= n; xi++){
		for (int xf = xi; xf <= n; xf++){
			// Initializing.
			dp[1] = query(1, xi, xf);

			// Calculating maximum sum ending in column j between lines xi and xf.
			for (int j = 2; j <= m; j++){
				dp[j] = max(dp[j - 1] + query(j, xi, xf), query(j, xi, xf));
			}

			// Updating answer.
			ans = max(ans, *max_element(dp + 1, dp + 1 + m));
		}
	}

	return ans;
}