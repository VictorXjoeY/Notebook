#define N 1000

vector<pair<int, int> > g[N + 1];
int dist[N + 1];
int n;

/* O(V * E) Returns true if there is a negative cycle reachable from u. */
bool bellman_ford(int u){
	int v, w, i, j;

	// Initializing.
	memset(dist, 0x3f, sizeof(dist));
	dist[u] = 0;

	// Takes n - 1 iterations to converge.
	for (i = 1; i <= n - 1; i++){
		// For every vertex u.
		for (u = 1; u <= n; u++){
			// For every edge (u, v).
			for (j = 0; j < (int)g[u].size(); j++){
				v = g[u][j].first;
				w = g[u][j].second;

				// Trying to relax this edge.
				if (dist[u] + w < dist[v]){
					dist[v] = dist[u] + w;
				}
			}
		}
	}

	// For every vertex u.
	for (u = 1; u <= n; u++){
		// For every edge (u, v).
		for (i = 0; i < (int)g[u].size(); i++){
			v = g[u][i].first;
			w = g[u][i].second;

			// If I can still relax an edge after n - 1 iterations, I've found a negative cycle.
			if (dist[u] + w < dist[v]){
				return true;
			}
		}
	}

	// No negative cycle reachable from u.
	return false;
}