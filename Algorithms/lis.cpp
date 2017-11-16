#define INF 0x3f3f3f3f
#define N 1000000

int a[N + 1];
int l[N + 1];
int n;

int lis(){
	int ans, p, i;

	// Init everyone as INF.
	memset(l, 0x3f3f, sizeof(l));

	// Init.
	l[0] = -INF;
	ans = 0;

	// LIS.
	for (i = 1; i <= n; i++){
		// Find position to place.
		p = lower_bound(l, l + N + 1, a[i]) - l;

		// Updating lis with size p ending in l[p] with minimum ending possible.
		l[p] = min(l[p], a[i]);

		// Updating answer.
		ans = max(ans, p);
	}

	return ans;
}