constexpr int N = 300;

vector<pair<int, int>> g[N + 1]; // (Input)
int dist[N + 1][N + 1];
int n; // (Input)

/* O(V^3) - Returns true if there's a negative cycle in the graph. */
bool floyd_warshall() {
	// Initializing.
	memset(dist, 0x3f, sizeof(dist));

	// Filling distance matrix with the edges.
	for (int u = 1; u <= n; u++) {
		dist[u][u] = 0;

		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i].first;
			int w = g[u][i].second;
			dist[u][v] = w;
		}
	}

	// For every intermediate vertex k.
	for (int k = 1; k <= n; k++) {
		// For every starting vertex i.
		for (int i = 1; i <= n; i++) {
			// For every ending vertex j.
			for (int j = 1; j <= n; j++) {
				// If there is a better path using k as intermediate vertex.
				if (dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}

	// Checking for negative cycles.
	for (int u = 1; u <= n; u++) {
		if (dist[u][u] < 0) {
			return true; // u belongs to a negative cycle.
		}
	}

	// No negative cycles.
	return false;
}