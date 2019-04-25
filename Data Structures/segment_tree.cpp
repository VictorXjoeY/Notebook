#define LEFT(x) (x << 1)
#define RIGHT(x) ((x << 1) | 1)
#define N 100000

int a[N + 1]; // (Input)
int seg[4 * N + 1];
int lazy[4 * N + 1];

/* O(1) - Updates the current node with lazy and flusshes down the lazyness. */
void lazy_update(int cur, int l, int r){
	// Updating it.
	seg[cur] += lazy[cur];

	// If not a leaf node.
	if (l != r){
		// Marking children as lazy.
		lazy[LEFT(cur)] += lazy[cur];
		lazy[RIGHT(cur)] += lazy[cur];
	}

	// Marking current node as not lazy.
	lazy[cur] = 0;
}

/* O(1) - Merges the children's values. */
int merge(int nl, int nr){
	return max(nl, nr);
}

/* O(N) - Builds a Segment Tree "seg" out of the array "a". */
void build(int cur, int l, int r){
	int m = (l + r) / 2;

	// Leaf node.
	if (l == r){
		seg[cur] = a[l];
		return;
	}

	// Going down both ways.
	build(LEFT(cur), l, m);
	build(RIGHT(cur), m + 1, r);

	// Merging children's results.
	seg[cur] = merge(seg[LEFT(cur)], seg[RIGHT(cur)]);
}

/* O(Log(N)) - Updates the range [i..j]. */
void update(int cur, int l, int r, int i, int j, int x){
	int m = (l + r) / 2;

	// Updates current node with lazy if it needs an update.
	if (lazy[cur] != 0){
		lazy_update(cur, l, r);
	}

	// [l..r] is outside update range [i..j].
	if (l > j or r < i){
		return;
	}

	// [l..r] is fully inside the update range [i..j].
	if (l >= i and r <= j){
		// Updating with x.
		lazy[cur] = x;
		lazy_update(cur, l, r);
		return;
	}

	// Going down both ways.
	update(LEFT(cur), l, m, i, j, x);
	update(RIGHT(cur), m + 1, r, i, j, x);

	// Merging children's results.
	seg[cur] = merge(seg[LEFT(cur)], seg[RIGHT(cur)]);
}

/* O(Log(N)) - Returns the content of the range [i, j] of the Segment Tree. */
int query(int cur, int l, int r, int i, int j){
	int nl, nr, m = (l + r) / 2;

	// Updates current node with lazy if it needs an update.
	if (lazy[cur] != 0){
		lazy_update(cur, l, r);
	}

	// [l..r] is outside query range [i..j].
	if (l > j or r < i){
		// Returning a value that will not affect the result.
		return 0;
	}

	// [l..r] is fully inside the query range [i..j].
	if (l >= i and r <= j){
		return seg[cur];
	}

	// Going down both ways.
	nl = query(LEFT(cur), l, m, i, j);
	nr = query(RIGHT(cur), m + 1, r, i, j);

	// Merging children's results.
	seg[cur] = merge(seg[LEFT(cur)], seg[RIGHT(cur)]);

	// Merging the query results.
	return merge(nl, nr);
}