constexpr int N = 1000;

vector<pair<int, int>> g[N + 1]; // (Input)
int dist[N + 1];
int n; // (Input)

/* O(V * E) - Returns true if there is a negative cycle somewhere in the graph. */
bool bellman_ford(int u) {
    bool converged = false;

    // Initializing.
    memset(dist, 0x3f, sizeof(dist));
    dist[u] = 0;

    // It takes at most n - 1 iterations to converge if there are no negative cycles in the graph.
    for (int i = 1; !converged and i <= n; i++) {
        converged = true;

        // For every vertex u.
        for (int u = 1; u <= n; u++) {
            // For every edge (u, v).
            for (int j = 0; j < g[u].size(); j++) {
                int v = g[u][j].first;
                int w = g[u][j].second;

                // Trying to relax this edge.
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    converged = false;
                }
            }
        }
    }

    // Returns true if it didn't converge after n - 1 iterations.
    return !converged;
}