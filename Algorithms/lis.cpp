#define INF 0x3f3f3f3f
#define N 100000

int a[N + 1];
int l[N + 1];
int n;

/* O(N * log(N)). */
int lis(){
	int ans, p, i;

	// Initializing everyone as INF.
	memset(l, 0x3f, sizeof(l));

	// Initializing.
	l[0] = -INF;
	ans = 0;

	// Longest Increasing Subsequence.
	for (i = 1; i <= n; i++){
		// Find position to place.
		p = lower_bound(l, l + N + 1, a[i]) - l;

		// Updating LIS with size p ending in l[p] with minimum ending possible.
		l[p] = min(l[p], a[i]);

		// Updating answer.
		ans = max(ans, p);
	}

	// Returning length of the Longest Increasing Subsequence.
	return ans;
}