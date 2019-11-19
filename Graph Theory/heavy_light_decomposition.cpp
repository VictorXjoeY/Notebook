#define LEFT(x) (x << 1)
#define RIGHT(x) ((x << 1) | 1)

/* O(1) - Retrieves the index of the Most Significant Bit. */
constexpr int msb_index(int mask) {
	return 8 * sizeof(mask) - __builtin_clz(mask) - 1;
}

constexpr int N = 100000;
constexpr int L = msb_index(N - 1) + 1; // L = ceil(log(N))

vector<pair<int, long long>> g[N + 1]; // (Input)
bool seen[N + 1];
int parent[N + 1];
long long weight[N + 1];
int size[N + 1];
int depth[N + 1];
int d[N + 1]; // Discovery time, which represents the position in the Segment Tree.
int d_inv[N + 1];
long long lazy[1 << (L + 1)];
long long seg[1 << (L + 1)];
int chain[N + 1]; // chain[u] stores the chain index of the vertex u. chain[u] = u if u is the representative of his chain.
int timer;
int n; // (Input)

/* O(1) - Updates the current node with lazy and flushes down the lazyness. */
void lazy_update(int cur, int l, int r) {
	seg[cur] += (r - l + 1) * lazy[cur]; // Updating cur.

	// If not leaf node.
	if (l < r) {
		// Marking children as lazy.
		lazy[LEFT(cur)] += lazy[cur];
		lazy[RIGHT(cur)] += lazy[cur];
	}

	// Marking current node as not lazy.
	lazy[cur] = 0;
}

/* O(1). */
long long merge(long long nl, long long nr) {
	return nl + nr;
}

/* O(Log(N)) - Use update(1, 1, n, d[u], w) to update u with the value w. */
void update(int cur, int l, int r, int i, int j, long long w) {
	int m = (l + r) / 2;

	if (lazy[cur]) { // Propagate lazy.
		lazy_update(cur, l, r);
	}

	if (l > j or r < i) { // Out of range.
		return;
	}

	if (l >= i and r <= j) { // Fully in range.
		lazy[cur] = w;
		lazy_update(cur, l, r);
		return;
	}

	update(LEFT(cur), l, m, i, j, w);
	update(RIGHT(cur), m + 1, r, i, j, w);

	seg[cur] = merge(seg[LEFT(cur)], seg[RIGHT(cur)]);
}

/* O(Log^2(N)) - Updates the path between u and v. */
void hld_update(int u, int v, long long w) {
	// While u and v don't belong to the same chain.
	while (chain[u] != chain[v]) {
		if (depth[chain[u]] > depth[chain[v]]) { // Going up u's chain.
			update(1, 1, n, d[chain[u]], d[u], w);
			u = parent[chain[u]];
		}
		else{ // Going up v's chain.
			update(1, 1, n, d[chain[v]], d[v], w);
			v = parent[chain[v]];
		}
	}
	
	// Remove "+1" and manually fill weight[] to make updates on vertices instead of updates on edges.
	update(1, 1, n, min(d[u], d[v]) + 1, max(d[u], d[v]), w); // min(d[u], d[v]) is the time of discovery of lca(u, v).
}

/* O(Log(N)) - Use query(1, 1, n, min(d[u], d[v]) + 1, max(d[u], d[v])) if chain[u] == chain[v]. (Remove +1 to query on vertices) */
long long query(int cur, int l, int r, int i, int j) {
	int m = (l + r) / 2;
	long long nl, nr;

	if (lazy[cur]) { // Propagate lazy.
		lazy_update(cur, l, r);
	}

	if (l > j or r < i) { // Out of range.
		return 0;
	}

	if (l >= i and r <= j) { // Fully in range.
		return seg[cur];
	}

	nl = query(LEFT(cur), l, m, i, j);
	nr = query(RIGHT(cur), m + 1, r, i, j);
	
	seg[cur] = merge(seg[LEFT(cur)], seg[RIGHT(cur)]);

	return merge(nl, nr);
}

/* O(Log^2(N)) - Queries the path between u and v. */
long long hld_query(int u, int v) {
	long long ans = 0;

	// While u and v don't belong to the same chain.
	while (chain[u] != chain[v]) {
		if (depth[chain[u]] > depth[chain[v]]) { // Going up u's chain.
			ans = merge(ans, query(1, 1, n, d[chain[u]], d[u]));
			u = parent[chain[u]];
		}
		else{ // Going up v's chain.
			ans = merge(ans, query(1, 1, n, d[chain[v]], d[v]));
			v = parent[chain[v]];
		}
	}
	
	// Remove "+1" and manually fill weight[] to make queries on vertices instead of queries on edges.
	ans = merge(ans, query(1, 1, n, min(d[u], d[v]) + 1, max(d[u], d[v]))); // min(d[u], d[v]) is the time of discovery of lca(u, v).

	return ans;
}

/* O(V). */
void build(int cur, int l, int r) {
	int u, m = (l + r) / 2;

	if (l == r) {
		// Obtaining the vertex with discovery time equal to l.
		u = d_inv[l];
		seg[cur] = weight[u];
		return;
	}

	build(LEFT(cur), l, m);
	build(RIGHT(cur), m + 1, r);

	seg[cur] = merge(seg[LEFT(cur)], seg[RIGHT(cur)]);
}

/* O(V) - Fills d[], d_inv[] and chain[]. */
void dfs_hld(int u) {
	d[u] = ++timer;
	d_inv[d[u]] = u;

	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].first;
		chain[v] = (i == 0 ? chain[u] : v); // Creates a new chain for every i != 0.
		dfs_hld(v);
	}
}

/* O(V) - Fills parent[], weight[], size[] and depth[]. */
void dfs_init(int u, int cur_depth) {
	seen[u] = true;
	size[u] = 1;
	depth[u] = cur_depth;

	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].first;
		long long w = g[u][i].second;

		if (!seen[v]) {
			dfs_init(v, cur_depth + 1);
			parent[v] = u;
			weight[v] = w;
			size[u] += size[v];
		}
	}
}

/* O(V) - Builds the Heavy-Light structure. */
void hld_init(int root) {
	// Initializing.
	memset(seen, false, sizeof(seen));
	memset(size, 0, sizeof(size));
	parent[root] = 0;
	weight[root] = 0; // For edges query.

	dfs_init(root, 0);

	// Clears graph.
	for (int u = 1; u <= n; u++) {
		g[u].clear();
	}

	// Transforms the undirected tree into a directed tree.
	for (int u = 1; u <= n; u++) {
		if (u != root) {
			g[parent[u]].push_back({u, weight[u]});
		}
	}

	// Place the child v with the greatest subtree first in the adjacency list of u.
	for (int u = 1; u <= n; u++) {
		for (int i = 1; i < g[u].size(); i++) {
			if (size[g[u][i].first] > size[g[u][0].first]) {
				swap(g[u][i], g[u][0]);
			}
		}
	}

	// Building chains.
	timer = 0;
	chain[root] = root;
	dfs_hld(root);

	// Building Segment Tree.
	memset(lazy, 0, sizeof(lazy)); // Clearing lazy.
	build(1, 1, n);
}
