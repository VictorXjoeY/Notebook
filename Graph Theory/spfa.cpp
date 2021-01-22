constexpr int N = 1000;

vector<pair<int, int>> g[N + 1]; // (Input)
bool in_queue[N + 1];
int dist[N + 1];
int n; // (Input)

/* O(V * E) - Returns true if there is a negative cycle reachable from u.
   Connect an extra vertex 0 to every other vertex with weight -1 and call spfa(0) to detect negative cycles in the entire graph. */
bool spfa(int u) {
    vector<int> cur;
    queue<int> q;

    // Clearing.
    memset(in_queue, false, sizeof(in_queue));
    memset(dist, 0x3f, sizeof(dist));

    // Initializing.
    dist[u] = 0;
    in_queue[u] = true;
    q.push(u);

    // It takes at most n - 1 iterations to converge if there are no negative cycles in the graph.
    for (int i = 1; !q.empty() and i <= n; i++) {
        // Retrieving every vertex from the queue.
        while (!q.empty()) {
            cur.push_back(q.front());
            q.pop();
        }

        // For every vertex u in the queue.
        for (int j = 0; j < cur.size(); j++) {
            u = cur[j];
            in_queue[u] = false;

            // For every edge (u, v).
            for (int k = 0; k < g[u].size(); k++) {
                int v = g[u][k].first;
                int w = g[u][k].second;

                // Trying to relax this edge.
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;

                    if (!in_queue[v]) {
                        in_queue[v] = true;
                        q.push(v);
                    }
                }
            }
        }

        cur.clear();
    }

    // Returns true if it didn't converge after n - 1 iterations.
    return !q.empty();
}