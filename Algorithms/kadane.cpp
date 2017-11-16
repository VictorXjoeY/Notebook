#define N 1000000

int a[N + 1];
int dp[N + 1];
int n;

int kadane(){
	int i;

	// Init.
	dp[1] = a[1];

	// Calculating maximum sum ending in a[i].
	for (i = 2; i <= n; i++){
		dp[i] = max(dp[i - 1] + a[i], a[i]);
	}

	// Returning maximum sub-array sum.
	return *max_element(dp + 1, dp + 1 + n);
}