/* O(1) - Retrieves the index of the Most Significant Bit. */
constexpr int msb_index(int mask) {
	return 8 * sizeof(mask) - __builtin_clz(mask) - 1;
}

constexpr int MIN = 1;
constexpr int MAX = 1000000000;
constexpr int Q = 100000; // Number of range updates.
constexpr int L = msb_index(MAX - MIN); // Greatest L such that 2^L <= (MAX - MIN + 1) - 1
constexpr int LQ = msb_index(Q); // Greatest LQ such that 2^LQ <= Q

// Every node in this tree other than the leaves have 2 children. Leaves have seg[cur] = 0 but will have a lazy[cur] != 0 after updates.
// The tree can have at most exactly 2^(LQ + 3) + 4 * (L - LQ - 1) * Q - 1 nodes, which can be approximated by 4 * (L - LQ + 1) * Q - 1.
// Assumes that L >= LQ.
long long seg[4 * (L - LQ + 1) * Q - 1]; // seg[0] should store the neutral value for the merge operation.
long long lazy[4 * (L - LQ + 1) * Q - 1];
int lchild[4 * (L - LQ + 1) * Q - 1];
int rchild[4 * (L - LQ + 1) * Q - 1];
int root, last;

/* O(1) - Returns the real value of the node, considering its lazy value. */
long long value(int cur, int l, int r) {
	return seg[cur] + (r - l + 1) * lazy[cur];
}

/* O(1) - Updates the current node with lazy and flushes down the lazyness. */
void lazy_update(int cur, int l, int r) {
	seg[cur] = value(cur, l, r);

	if (l < r) { // Not a length 1 range.
		if (!lchild[cur]) { // Creating left child.
			lchild[cur] = ++last;
		}

		if (!rchild[cur]) { // Creating right child.
			rchild[cur] = ++last;
		}

		// Marking children as lazy.
		lazy[lchild[cur]] += lazy[cur];
		lazy[rchild[cur]] += lazy[cur];
	}

	// Marking current node as not lazy.
	lazy[cur] = 0;
}

/* O(1) - Merges the children's values. */
long long merge(long long nl, long long nr) {
	return nl + nr;
}

/* O(Log(MAX)) - Call root = update(root, MIN, MAX, i, j, x) */
int update(int cur, int l, int r, int i, int j, long long x) {
	int m = (l + r) / 2;

	if (l > j or r < i) { // Out of range.
		return cur;
	}

	if (!cur) { // Creating the current range.
		cur = ++last;
	}

	if (l >= i and r <= j) { // Fully in range.
		lazy[cur] += x;
		return cur;
	}

	// Only flush down the lazyness if we're going to call for children nodes.
	if (lazy[cur]) {
		lazy_update(cur, l, r);
	}

	// Updating children and linking the tree.
	lchild[cur] = update(lchild[cur], l, m, i, j, x);
	rchild[cur] = update(rchild[cur], m + 1, r, i, j, x);

	// Merging children's results.
	seg[cur] = merge(value(lchild[cur], l, m), value(rchild[cur], m + 1, r));

	return cur;
}

/* O(Log(MAX)) - Call ans = query(root, MIN, MAX, i, j) */
long long query(int cur, int l, int r, int i, int j) {
	int m = (l + r) / 2;
	long long nl, nr;

	if (l > j or r < i) { // Out of range.
		return 0;
	}

	if (l >= i and r <= j) { // Fully in range.
		return value(cur, l, r);
	}

	if (!lchild[cur] and !rchild[cur]) { // Leaf but l < r.
		return value(cur, max(l, i), min(r, j));
	}

	// Only flush down the lazyness if we're going to call for children nodes.
	if (lazy[cur]) {
		lazy_update(cur, l, r);
	}

	// Has both children, querying downwards.
	nl = query(lchild[cur], l, m, i, j);
	nr = query(rchild[cur], m + 1, r, i, j);

	return merge(nl, nr);
}