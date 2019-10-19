/* O(1) - Retrieves the index of the Most Significant Bit. */
constexpr int msb_index(int mask){
	return 8 * sizeof(mask) - __builtin_clz(mask) - 1;
}

constexpr int N = 100000;
constexpr int L = msb_index(N); // Greatest L such that 2^L <= N

int ancestor[N + 1][L + 1];
vector<int> g[N + 1]; // (Input)
int parent[N + 1];
int depth[N + 1];
bool seen[N + 1];

/* O(V) - Depth-First Search to compute depths. */
void dfs(int u, int d){
	seen[u] = true;
	depth[u] = d;

	for (int i = 0; i < (int)g[u].size(); i++){
		int v = g[u][i];

		if (!seen[v]){
			dfs(v, d + 1);
			parent[v] = u;
		}
	}
}

/* O(V * Log(V)). */
void lca_init(int root){
	// Initializing.
	memset(depth, -1, sizeof(depth));
	memset(parent, -1, sizeof(parent));
	memset(ancestor, -1, sizeof(ancestor));
	memset(seen, false, sizeof(seen));

	// Computing the depth and the parent arrays.
	dfs(root, 0);

	// Base case for Dynamic Programming.
	for (int i = 1; i <= N; i++){
		ancestor[i][0] = parent[i];
	}

	// For each j.
	for (int j = 1; j <= L; j++){
		// For each vertex i.
		for (int i = 1; i <= N; i++){
			// If it has 2^(j - 1) ancestor.
			if (ancestor[i][j - 1] != -1){
				// 2^j ancestor of vertex i is the 2^(j - 1) ancestor of 2^(j - 1) ancestor of i.
				ancestor[i][j] = ancestor[ancestor[i][j - 1]][j - 1];
			}
		}
	}
}

/* O(Log(V)). */
int lca(int u, int v){
	// Making u the deepest vertex.
	if (depth[u] < depth[v]){
		swap(u, v);
	}

	// Getting u to the same depth as v by making "jumps" to its 2^i ancestors for each i.
	for (int i = L; i >= 0; i--){
		// If jumping to u's 2^i ancestor doesn't make it pass vertex v's depth.
		if (depth[u] - (1 << i) >= depth[v]){
			u = ancestor[u][i];
		}
	}

	// If u and v are the same.
	if (u == v){
		return u;
	}

	// Making u and v "jump" up without making them go up to lca(u, v) or above.
	for (int i = L; i >= 0; i--){
		// Only jump if the jump makes them go below lca(u, v).
		if (ancestor[u][i] != ancestor[v][i]){
			u = ancestor[u][i];
			v = ancestor[v][i];
		}
	}

	// At the end, u and v are one level deeper than lca(u, v).
	return parent[u];
}