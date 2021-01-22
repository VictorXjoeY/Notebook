constexpr int INF = 0x3f3f3f3f;
constexpr int N = 100000;

int a[N + 1]; // (Input)
int l[N + 1];
int n; // (Input)

/* O(N * log(N)). */
int lis() {
    int ans, p;

    // Initializing everyone as INF.
    memset(l, 0x3f, sizeof(l));

    // Initializing.
    l[0] = -INF;
    ans = 0;

    // Longest Increasing Subsequence.
    for (int i = 1; i <= n; i++) {
        // Find position to place.
        p = lower_bound(l, l + n + 1, a[i]) - l;

        // Updating LIS with size p ending in l[p] with minimum ending possible.
        l[p] = min(l[p], a[i]);

        // Updating answer.
        ans = max(ans, p);
    }

    // Returning length of the Longest Increasing Subsequence.
    return ans;
}
