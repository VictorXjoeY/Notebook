#define N 1000

vector<pair<int, int> > g[N + 1];
int dist[N + 1];
int n;

/* O(V * E) - Returns true if there is a negative cycle reachable from u. */
bool bellman_ford(int u){
	int v, w, i, j;
	bool converged;

	// Initializing.
	memset(dist, 0x3f, sizeof(dist));
	dist[u] = 0;

	// It takes at most n - 1 iterations to converge if there is no negative cycle reachable from u.
	for (i = 1, converged = false; converged and i <= n; i++){
		converged = true;

		// For every vertex u.
		for (u = 1; u <= n; u++){
			// For every edge (u, v).
			for (j = 0; j < (int)g[u].size(); j++){
				v = g[u][j].first;
				w = g[u][j].second;

				// Trying to relax this edge.
				if (dist[u] + w < dist[v]){
					dist[v] = dist[u] + w;
					converged = false;
				}
			}
		}
	}

	// Returns true if it didn't converge after n - 1 iterations.
	return !converged;
}