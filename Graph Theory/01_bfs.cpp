constexpr int N = 100000;

vector<pair<int, bool>> g[N + 1]; // (Input)
int dist[N + 1];
bool seen[N + 1];

/* O(V + E). */
void bfs_01(int u) {
    deque<int> q;

    // Initializing.
    memset(seen, false, sizeof(seen));
    memset(dist, 0x3f, sizeof(dist));
    dist[u] = 0;
    q.push_back(u);

    // While there are vertices to visit.
    while (!q.empty()) {
        u = q.front();
        q.pop_front();

        if (!seen[u]) {
            seen[u] = true;

            // For every vertex v adjacent to u.
            for (int i = 0; i < g[u].size(); i++) {
                int v = g[u][i].first;
                bool w = g[u][i].second;

                // If vertex v wasn't already visited and the distance is improved by (u, v).
                if (!seen[v] and dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;

                    if (w) { // Weight 1, push back.
                        q.push_back(v);
                    } else { // Weight 0, push front.
                        q.push_front(v);
                    }
                }
            }
        }
    }
}