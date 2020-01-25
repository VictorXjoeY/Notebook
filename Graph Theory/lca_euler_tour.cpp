constexpr int N = 100000;

class SparseTable {
private:
	vector<vector<int>> table;
	vector<int> a;

	/* O(1) - Retrieves the index of the Most Significant Bit. */
	int msb_index(int mask) {
		return 8 * sizeof(mask) - __builtin_clz(mask) - 1;
	}

	/* O(1) - Retrieves ceil(log2(n)). */
	int floor_log2(int n) {
		assert(n > 0);
		return msb_index(n);
	}

	/* O(1) - Idempotent operation. f(f(x)) = f(x) or f(f(x, y), y) = f(x, f(x, y)) = f(x, y). */
	int merge(int x, int y) {
		return a[x] < a[y] ? x : y;
	}

public:
	SparseTable() {}

	/* O(N * Log(N)). */
	SparseTable(vector<int> const& a) {
		this->a = a;
		int k = msb_index(a.size());

		// Allocating memory.
		table.resize(k + 1);

		for (int j = 0; j <= k; j++) {
			table[j].resize(a.size() - (1 << j) + 1);
		}

		// Base.
		for (int i = 0; i < a.size(); i++) {
			table[0][i] = i;
		}

		// Building for each 2^j <= n
		for (int j = 1; j <= k; j++) {
			// Building for each [i, i + 2^j - 1]
			for (int i = 0; i + (1 << j) - 1 < a.size(); i++) {
				table[j][i] = merge(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
			}
		}
	}

	/* O(1). */
	int query(int l, int r) {
		// Finding greatest k such that 2^k <= r - l + 1
		int k = floor_log2(r - l + 1);
		return merge(table[k][l], table[k][r - ((1 << k) - 1)]);
	}
};

SparseTable st;
vector<int> g[N + 1]; // (Input)
int euler[2 * N];
int depth[2 * N];
int first[N + 1];
bool seen[N + 1];
int timer;
int n; // (Input)

/* O(V) - Depth-First Search to compute Euler Tour and depths. */
void dfs(int u, int d) {
	seen[u] = true;

	// Pushing u into Euler Tour.
	timer++;
	first[u] = timer;
	euler[timer] = u;
	depth[timer] = d;

	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];

		if (!seen[v]) {
			dfs(v, d + 1);
			
			// Pushing u into Euler Tour.
			timer++;
			euler[timer] = u;
			depth[timer] = d;
		}
	}
}

/* O(V * Log(V)). */
void lca_init(int root) {
	// Clearing.
	memset(seen, false, sizeof(seen));
	timer = 0;

	// Building.
	dfs(root, 0);
	st = SparseTable(vector<int>(depth, depth + 2 * n));
}

/* O(1). */
int lca(int u, int v) {
	// Retrieving vertex with minimum depth between first[u] and first[v] in Euler Tour.
	return euler[st.query(min(first[u], first[v]), max(first[u], first[v]))];
}
