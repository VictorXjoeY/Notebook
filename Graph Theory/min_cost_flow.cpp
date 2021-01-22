// If there are lots of parallel edges in the residual graph you can merge them to achieve a better runtime.
constexpr int INF = 0x3f3f3f3f; // Has to be greater or equal to maximum flow.
constexpr int N = 500;
constexpr int FNN = N;

vector<tuple<int, long long, int>> g[FNN + 1]; // (Input) Original graph, g[u] stores tuples (v, cost, capacity).
vector<tuple<int, long long, int>> r[FNN + 1]; // Residual graph, r[u] stores tuples (v, cost, current capacity).
pair<int, int> parent[FNN + 1];                // parent[u] stores (v, i) such that v is the parent of u and u == r[v][i].first.
vector<int> flow[FNN + 1];                     // Flow graph, f[u][i] stores the flow going through the edge (u, r[u][i]).
vector<int> rev[FNN + 1];                      // Reverse edge mapping, rev[u][i] stores the index j such that u == r[r[u][i].first][j].first.
int pflow[FNN + 1];                            // pflow[u] stores the amount of flow going from the source to u in the path defined by the parent array.
long long dist[FNN + 1];
bool in_queue[FNN + 1];
int fnn; // (Input) Number of vertices in the flow network.

/* O(V * E). */
int spfa(int s, int t) {
    vector<int> cur;
    queue<int> q;

    // Clearing.
    memset(in_queue, false, sizeof(in_queue));
    memset(dist, 0x3f, sizeof(dist));
    memset(pflow, 0, sizeof(pflow));

    // Initializing.
    parent[s] = {s, -1};
    pflow[s] = INF; // Source has infinite flow.
    in_queue[s] = true;
    dist[s] = 0;
    q.push(s);

    // It takes at most fnn - 1 iterations to converge if there are no negative cycles in the graph.
    for (int i = 1; !q.empty() and i <= fnn; i++) {
        // Retrieving every vertex from the queue.
        while (!q.empty()) {
            cur.push_back(q.front());
            q.pop();
        }

        // For every vertex u in the queue.
        for (int j = 0; j < cur.size(); j++) {
            int u = cur[j];
            in_queue[u] = false;

            // For every edge (u, v).
            for (int k = 0; k < r[u].size(); k++) {
                int v = get<0>(r[u][k]);
                long long w = get<1>(r[u][k]);
                int c = get<2>(r[u][k]);

                // If we can relax this edge and push a positive amount of flow.
                if (dist[u] + w < dist[v] and c > 0) {
                    // Updating v.
                    dist[v] = dist[u] + w;
                    parent[v] = {u, k};
                    pflow[v] = min(c, pflow[u]);

                    if (!in_queue[v]) {
                        in_queue[v] = true;
                        q.push(v);
                    }
                }
            }
        }

        cur.clear();
    }

    // Returns the flow at the sink.
    return pflow[t];
}

/* O(min(F, V * E) * V * E) such that F is the maximum flow.
   Returns the maximum flow pushed (bounded by k) and the minimum cost to push that amount of flow.
   Call min_cost_flow(s, t, INF) to obtain the min cost max flow. */
pair<int, long long> min_cost_flow(int s, int t, int k) {
    pair<int, long long> ans;
    int f;

    // Clearing.
    for (int u = 1; u <= fnn; u++) {
        flow[u].clear();
        rev[u].clear();
        r[u].clear();
    }

    // O(V + E) - Creating residual graph, reverse edge pointers and flow graph.
    for (int u = 1; u <= fnn; u++) {
        for (int i = 0; i < g[u].size(); i++) {
            int v = get<0>(g[u][i]);
            long long w = get<1>(g[u][i]);
            int c = get<2>(g[u][i]);

            if (u != v) {                      // Ignoring self-loops.
                rev[u].push_back(r[v].size()); // Reverse edge reference.
                rev[v].push_back(r[u].size()); // Reverse edge reference.
                r[u].push_back({v, w, c});     // Adding edge (u, v).
                r[v].push_back({u, -w, 0});    // Adding reverse edge (v, u).
                flow[u].push_back(0);          // Flow through edge (u, v).
                flow[v].push_back(0);          // Flow through edge (v, u).
            }
        }
    }

    ans = {0, 0};

    // O(min(F, V * E) * E) - While I can improve the flow.
    while (k > 0 and (f = spfa(s, t))) {
        // Updating the flow in the path found by the SPFA.
        int v = t;
        f = min(f, k);

        while (v != s) {
            // Adding f flow to (u, v).
            int u = parent[v].first;
            int i = parent[v].second;
            int j = rev[u][i]; // Reverse edge index.

            // Updating capacities in the residual graph.
            get<2>(r[u][i]) -= f;
            get<2>(r[v][j]) += f;

            // Updating flow graph.
            flow[u][i] += f;
            flow[v][j] -= f;

            // Updating the total cost with the cost of pushing the flow through the edge (u, v).
            ans.second += get<1>(r[u][i]) * f;

            v = u;
        }

        // Increasing the total flow.
        ans.first += f;
        k -= f;
    }

    return ans;
}