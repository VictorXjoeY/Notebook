#define N 100000

int dp[N + 1];
int a[N + 1]; // (Input)
int n; // (Input)

/* O(N). */
int kadane(){
	int i;

	// Initializing.
	dp[1] = a[1];

	// Calculating maximum sum ending in a[i].
	for (i = 2; i <= n; i++){
		dp[i] = max(dp[i - 1] + a[i], a[i]);
	}

	// Returning maximum sub-array sum.
	return *max_element(dp + 1, dp + 1 + n);
}