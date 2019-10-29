/* O(1) - Retrieves the index of the Most Significant Bit. */
constexpr int msb_index(int mask) {
	return 8 * sizeof(mask) - __builtin_clz(mask) - 1;
}

constexpr int N = 100000;
constexpr int T = 100000;
constexpr int L = msb_index(N - 1) + 1; // L = ceil(log(N))

// The persistent segment tree uses exactly 2 * N - 1 + T * (ceil(log(N)) + 1) nodes in the worst case.
// 2 * N - 1 initial nodes + (L + 1) nodes for each one of the T updates.
int root[T + 1];
long long seg[2 * N + T * (L + 1)];
int lchild[2 * N + T * (L + 1)];
int rchild[2 * N + T * (L + 1)];
int a[N + 1]; // (Input)
int last;

/* O(1) - Merges the children's values. */
long long merge(long long nl, long long nr) {
	return nl + nr;
}

/* O(N) - Use root[0] = build(1, n) */
int build(int l, int r) {
	int cur, m = (l + r) / 2;

	cur = ++last;

	if (l == r) {
		seg[cur] = a[l];
		return cur;
	}

	lchild[cur] = build(l, m);
	rchild[cur] = build(m + 1, r);

	seg[cur] = merge(seg[lchild[cur]], seg[rchild[cur]]);

	return cur;
}

/* O(Log(N)) - Use root[t] = update(root[t - 1], 1, n, p, x) */
int update(int cur, int l, int r, int p, long long x) {
	int ncur, m = (l + r) / 2;

	if (l > p or r < p) {
		return cur;
	}

	ncur = ++last;

	if (l == r) {
		// Creating new leaf node.
		seg[ncur] = x;
		return ncur;
	}

	// Creating new internal node and linking with children.
	lchild[ncur] = update(lchild[cur], l, m, p, x);
	rchild[ncur] = update(rchild[cur], m + 1, r, p, x);

	// Calculating new internal node.
	seg[ncur] = merge(seg[lchild[ncur]], seg[rchild[ncur]]);

	return ncur;
}

/* O(Log(N)) - Use query(root[k], 1, n, l, r) to query after the k'th update */
long long query(int cur, int l, int r, int i, int j) {
	int m = (l + r) / 2;
	long long nl, nr;

	if (l > j or r < i) {
		return 0;
	}

	if (l >= i and r <= j) {
		return seg[cur];
	}

	nl = query(lchild[cur], l, m, i, j);
	nr = query(rchild[cur], m + 1, r, i, j);

	return merge(nl, nr);
}
