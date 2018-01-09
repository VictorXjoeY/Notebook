#define INF 0x3f3f3f3f

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

	// Updates the current node with lazy and flusshes down the lazyness.
	void lazy_update(int cur, int l, int r){
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
	}

	// Merges the children's values.
	int merge(int nl, int nr){
		return max(nl, nr);
	}

	// Builds a Segment Tree "st" out of the vector "v".
	void build(int cur, int l, int r){
		int m = (l + r) / 2;

		// Leaf node.
		if (l == r){
			st[cur] = v[l];
			return;
		}

		// Going down both ways.
		build(LEFT(cur), l, m);
		build(RIGHT(cur), m + 1, r);

		// Merging children's results.
		st[cur] = merge(st[LEFT(cur)], st[RIGHT(cur)]);
	}

	// Updates the range [i..j].
	void update(int cur, int l, int r, int i, int j, int x){
		int m = (l + r) / 2;

		// Updating current node with lazy.
		lazy_update(cur, l, r);

		// [l..r] is outside update range [i..j].
		if (l > j or r < i){
			return;
		}

		// [l..r] is fully inside the update range [i..j].
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
		update(LEFT(cur), l, m, i, j, x);
		update(RIGHT(cur), m + 1, r, i, j, x);

		// Merging children's results.
		st[cur] = merge(st[LEFT(cur)], st[RIGHT(cur)]);
	}

	// Returns the content of the range [i, j] of the Segment Tree.
	int query(int cur, int l, int r, int i, int j){
		int nl, nr, m;

		m = (l + r) / 2;

		// Updating current node with lazy.
		lazy_update(cur, l, r);

		// [l..r] is outside query range [i..j].
		if (l > j or r < i){
			// Returning a value that will not affect the result.
			return -INF;
		}

		// [l..r] is fully inside the query range [i..j].
		if (l >= i and r <= j){
			return st[cur];
		}

		// Going down both ways.
		nl = query(LEFT(cur), l, m, i, j);
		nr = query(RIGHT(cur), m + 1, r, i, j);

		// Merging children's results.
		st[cur] = merge(st[LEFT(cur)], st[RIGHT(cur)]);

		// Merging the query results.
		return merge(nl, nr);
	}

public:
	SegmentTree(){}

	SegmentTree(int *v, int n){
		int i;

		lazy.assign(4 * (n + 1) + 1, 0);
		st.resize(4 * (n + 1) + 1);
		this->v.resize(n + 1);
		this->n = n;

		for (i = 1; i <= n; i++){
			this->v[i] = v[i];
		}

		build(1, 1, n);
	}

	void update(int i, int j, int x){
		update(1, 1, n, i, j, x);
	}

	int query(int i, int j){
		return query(1, 1, n, i, j);
	}
};