constexpr int N = 100000;

vector<pair<int, int>> g[N + 1]; // (Input)
bool in_mst[N + 1];
int cost[N + 1];
int n; // (Input)

/* O(V) - Retrieves next vertex to be added to Minimum Spanning Tree. */
int next_to_mst() {
	int v = 0;

	for (int u = 1; u <= n; u++) {
		if (!in_mst[u] and (!v or cost[u] < cost[v])) {
			v = u;
		}
	}

	return v;
}

/* O(V^2 + E). */
void prim(int u) {
	// Initializing.
	memset(in_mst, false, sizeof(in_mst));
	memset(cost, 0x3f, sizeof(cost));

	// Initializing source vertex. Cost of adding the first vertex u to Minimum Spanning Tree is 0.
	cost[u] = 0;

	// While there are vertices to visit.
	while ((u = next_to_mst())) {
		// Vertex u now belongs to Minimum Spanning Tree.
		in_mst[u] = true;

		// For every vertex v adjacent to u.
		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i].first;
			int w = g[u][i].second;

			// If a lower cost was found to add the vertex v to the Minimum Spanning Tree.
			if (!in_mst[v] and w < cost[v]) {
				cost[v] = w;
			}
		}
	}
}