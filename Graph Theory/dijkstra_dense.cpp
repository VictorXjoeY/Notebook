constexpr int N = 100000;

vector<pair<int, int>> g[N + 1]; // (Input)
bool in_spt[N + 1];
int dist[N + 1];
int n; // (Input)

/* O(V) - Retrieves next vertex to be added to Shortest Path Tree. */
int next_to_spt() {
    int v = 0;

    for (int u = 1; u <= n; u++) {
        if (!in_spt[u] and (!v or dist[u] < dist[v])) {
            v = u;
        }
    }

    return v;
}

/* O(E + V^2). */
void dijkstra(int u) {
    // Initializing.
    memset(in_spt, false, sizeof(in_spt));
    memset(dist, 0x3f, sizeof(dist));

    // Initializing source vertex. Cost of adding the first vertex u to Shortest Path Tree is 0.
    dist[u] = 0;

    // While there are vertices to visit.
    while ((u = next_to_spt())) {
        // Vertex u now belongs to Shortest Path Tree.
        in_spt[u] = true;

        // For every vertex v adjacent to u.
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i].first;
            int w = g[u][i].second;

            // If a better path was found to add the vertex v to the Shortest Path Tree.
            if (!in_spt[v] and dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
}
