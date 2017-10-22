// 1-based Segment Tree with Lazy Propagation
// st[cur] represents v[l..r]
class SegmentTree{
private:
	vector<int> v, st, lazy;
	int n;

	inline int LEFT(int x){
		return (x << 1);
	}

	inline int RIGHT(int x){
		return ((x << 1) | 1);
	}

	inline int MID(int l, int r){
		return ((l + r) / 2);
	}

	// Builds a Segment Tree "st" out of the vector "v".
	void build(int cur, int l, int r){
		// Leaf node.
		if (l == r){
			st[cur] = v[l];
			return;
		}

		// Going down both ways.
		build(LEFT(cur), l, MID(l, r));
		build(RIGHT(cur), MID(l, r) + 1, r);

		// Merging children's results.
		st[cur] = max(st[LEFT(cur)], st[RIGHT(cur)]);
	}

	// Updates the range [i..j].
	void update(int cur, int l, int r, int i, int j, int x){
		// This node needs an update.
		if (lazy[cur] != 0){
			// Updating it.
			st[cur] += lazy[cur];

			// If not a leaf node.
			if (l != r){
				// Marking children as lazy.
				lazy[LEFT(cur)] += lazy[cur];
				lazy[RIGHT(cur)] += lazy[cur];
			}

			// Marking current node as not lazy.
			lazy[cur] = 0;
		}

		// [l..r] is outside update range [i..j].
		if (l > j or r < i){
			return;
		}

		// [l..r] is fully inside the range [i..j].
		if (l >= i and r <= j){
			// Updating with x.
			st[cur] += x;

			// If not a leaf node.
			if (l != r){
				// Marking children as lazy.
				lazy[LEFT(cur)] += x;
				lazy[RIGHT(cur)] += x;
			}

			return;
		}

		// Going down both ways.
		update(LEFT(cur), l, MID(l, r), i, j, x);
		update(RIGHT(cur), MID(l, r) + 1, r, i, j, x);

		// Merging children's results.
		st[cur] = max(st[LEFT(cur)], st[RIGHT(cur)]);
	}

	// Returns the content of the range [i, j] of the Segment Tree.
	int query(int cur, int l, int r, int i, int j){
		int r1, r2;

		// This node needs an update.
		if (lazy[cur] != 0){
			// Updating it.
			st[cur] += lazy[cur];

			// If not a leaf node.
			if (l != r){
				// Marking children as lazy.
				lazy[LEFT(cur)] += lazy[cur];
				lazy[RIGHT(cur)] += lazy[cur];
			}

			// Marking current node as not lazy.
			lazy[cur] = 0;
		}

		// [l..r] is outside query range [i..j].
		if (l > j or r < i){
			// Returning a value that will not affect the result.
			return -0x3f3f3f3f;
		}

		// [l..r] is fully inside the range [i..j].
		if (l >= i and r <= j){
			return st[cur];
		}

		// Going down both ways.
		r1 = query(LEFT(cur), l, MID(l, r), i, j);
		r2 = query(RIGHT(cur), MID(l, r) + 1, r, i, j);

		// Merging children's results.
		st[cur] = max(st[LEFT(cur)], st[RIGHT(cur)]);

		// Merging the query results.
		return max(r1, r2);
	}

public:
	SegmentTree(){}

	SegmentTree(int *v, int n){
		int i;

		lazy.assign(4 * (n + 1), 0);
		st.resize(4 * (n + 1));
		this->v.resize(n);
		this->n = n;

		for (i = 0; i < n; i++){
			this->v[i] = v[i];
		}

		build(1, 0, n - 1);
	}

	void update(int i, int j, int x){
		update(1, 0, n - 1, i, j, x);
	}

	int query(int i, int j){
		return query(1, 0, n - 1, i, j);
	}
};