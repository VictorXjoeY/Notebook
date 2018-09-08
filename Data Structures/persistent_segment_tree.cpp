#define N 100000
#define T 100000
#define L 17

int root[T + 1];
int seg[4 * L * N + 1];
int lchild[4 * L * N + 1];
int rchild[4 * L * N + 1];
int a[N + 1];
int n, last;

int merge(int nl, int nr){
	return nl + nr;
}

/* O(N) - Use root[0] = build(1, n) */
int build(int l, int r){
	int cur, m = (l + r) / 2;

	cur = ++last;

	if (l == r){
		seg[cur] = a[l];
		return cur;
	}

	lchild[cur] = build(l, m);
	rchild[cur] = build(m + 1, r);

	seg[cur] = merge(seg[lchild[cur]], seg[rchild[cur]]);

	return cur;
}

/* O(Log(N)) - Use root[t] = update(root[t - 1], 1, n, p, x) */
int update(int cur, int l, int r, int p, int x){
	int ncur, m = (l + r) / 2;

	if (l > p or r < p){
		return cur;
	}

	ncur = ++last;

	if (l == r){
		// Creating new leaf node.
		seg[ncur] = x;
		return ncur;
	}

	// Creating new internal node and linking with children.
	lchild[ncur] = update(lchild[cur], l, m, p, x);
	rchild[ncur] = update(rchild[cur], m + 1, r, p, x);

	// Calculating new internal node.
	seg[ncur] = merge(seg[lchild[ncur]], seg[rchild[ncur]]);
}

/* O(Log(N)) - Use query(root[k], 1, n, l, r) to query after the k'th update */
int query(int cur, int l, int r, int i, int j){
	int nl, nr, m = (l + r) / 2;

	if (l > j or r < i){
		return 0;
	}

	if (l >= i and r <= j){
		return seg[cur];
	}

	nl = query(lchild[cur], l, m, i, j);
	nr = query(rchild[cur], m + 1, r, i, j);

	return merge(nl, nr);
}