// If there are lots of parallel edges in the residual graph you can merge them to achieve a better runtime.
constexpr int INF = 0x3f3f3f3f; // Has to be greater or equal to maximum flow.
constexpr int N = 500;
constexpr int FNN = N;

vector<pair<int, int>> g[FNN + 1]; // (Input) Original graph, g[u] stores pairs (v, capacity).
vector<pair<int, int>> r[FNN + 1]; // Residual graph, r[u] stores pairs (v, current capacity).
pair<int, int> parent[FNN + 1]; // parent[u] stores (v, i) such that v is the parent of u and u == r[v][i].first.
vector<int> flow[FNN + 1]; // Flow graph, f[u][i] stores the flow going through the edge (u, r[u][i]).
vector<int> rev[FNN + 1]; // Reverse edge mapping, rev[u][i] stores the index j such that u == r[r[u][i].first][j].first.
int pflow[FNN + 1]; // pflow[u] stores the amount of flow going from the source to u in the path defined by the parent array.
bool seen[FNN + 1];
int fnn; // (Input) Number of vertices in the flow network.

/* O(V + E). */
int bfs(int s, int t) {
	queue<int> q;

	// Clearing.
	memset(seen, false, sizeof(seen));

	// Initializing.
	parent[s] = {s, -1};
	pflow[s] = INF; // Source has infinite flow.
	seen[s] = true;
	q.push(s);

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		// For every edge (u, v).
		for (int i = 0; i < r[u].size(); i++) {
			int v = r[u][i].first;
			int c = r[u][i].second; // Current capacity.

			// If it was not visited and we can push a positive amount of flow.
			if (!seen[v] and c > 0) {
				// Updating v.
				parent[v] = {u, i};
				pflow[v] = min(c, pflow[u]);
				seen[v] = true;

				if (v == t) { // Found a path from the source to the sink with flow pflow[v].
					return pflow[v];
				}

				// Pushing v into the queue.
				q.push(v);
			}
		}
	}

	return 0;
}

/* O(min(F, V * E) * E) such that F is the maximum flow. */
int edmonds_karp(int s, int t) {
	int ans, f;

	// Clearing.
	for (int u = 1; u <= fnn; u++) {
		flow[u].clear();
		rev[u].clear();
		r[u].clear();
	}

	// O(V + E) - Creating residual graph, reverse edge pointers and flow graph.
	for (int u = 1; u <= fnn; u++) {
		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i].first;
			int c = g[u][i].second;

			if (u != v) { // Ignoring self-loops.
				rev[u].push_back(r[v].size()); // Reverse edge reference.
				rev[v].push_back(r[u].size()); // Reverse edge reference.
				r[u].push_back({v, c}); // Adding edge (u, v).
				r[v].push_back({u, 0}); // Adding reverse edge (v, u).
				flow[u].push_back(0); // Flow through edge (u, v).
				flow[v].push_back(0); // Flow through edge (v, u).
			}
		}
	}

	ans = 0;

	// O(min(F, V * E) * E) - While I can improve the flow.
	while ((f = bfs(s, t))) {
		// Updating the flow in the path found by the BFS.
		int v = t;

		while (v != s) {
			// Adding f flow to (u, v).
			int u = parent[v].first;
			int i = parent[v].second;
			int j = rev[u][i]; // Reverse edge index.

			// Updating capacities in the residual graph.
			r[u][i].second -= f;
			r[v][j].second += f;

			// Updating flow graph.
			flow[u][i] += f;
			flow[v][j] -= f;

			v = u;
		}

		// Increasing the total flow.
		ans += f;
	}

	return ans;
}