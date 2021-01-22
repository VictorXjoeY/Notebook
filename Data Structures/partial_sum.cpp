constexpr int N = 100000;

int ans[N + 2];
int p[N + 2];
int n;

/* O(1) - Sums "value" to every element in the range [left, right] in ans lazy way. */
void update(int left, int right, int value) {
    p[left] += value;
    p[right + 1] -= value;
}

/* O(N) - Flushes all updates into array ans. */
void query() {
    for (int i = 1; i <= n; i++) {
        p[i] += p[i - 1];
        ans[i] += p[i];
    }

    memset(p, 0, sizeof(p));
}
