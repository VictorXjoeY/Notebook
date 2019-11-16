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
		r[u].clear();
	}

	// O(V + E) - Creating residual graph.
	for (int u = 1; u <= fnn; u++) {
		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i].first;
			int c = g[u][i].second;

			if (u != v) { // Ignoring self-loops.
				r[u].push_back({v, c});
				r[v].push_back({u, 0});
			}
		}
	}

	// O(E * Log(E)) - Merging parallel edges in the residual graph.
	for (int u = 1; u <= fnn; u++) {
		// Sorting so that parallel edges stay together.
		vector<pair<int, int>> adj = r[u];
		sort(adj.begin(), adj.end());
		r[u].clear();

		// Merging parallel edges.
		for (int i = 0; i < adj.size(); i++) {
			int v = adj[i].first;
			int c = adj[i].second;

			if (!r[u].empty() and v == r[u].back().first) {
				r[u].back().second += c;
			}
			else { // Pushing new edge.
				r[u].push_back({v, c});
			}
		}
	}

	// O(E * Log(E)) - Initializing flow and creating reverse edges references.
	for (int u = 1; u <= fnn; u++) {
		flow[u].assign(r[u].size(), 0);
		rev[u].resize(r[u].size());

		// For each edge (u, v).
		for (int i = 0; i < r[u].size(); i++) {
			int v = r[u][i].first;

			// Retrieving u's position in v's adjacency list.
			rev[u][i] = lower_bound(r[v].begin(), r[v].end(), make_pair(u, 0)) - r[v].begin();
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

/* O(V + E). */
void dfs(int u) {
	seen[u] = true;

	// For each edge (u, v).
	for (int i = 0; i < r[u].size(); i++) {
		int v = r[u][i].first;
		int c = r[u][i].second;

		// If v was not seen and the residual capacity of (u, v) is positive.
		if (!seen[v] and c > 0) {
			dfs(v);
		}
	}
}

/* O(min(F, V * E) * E) such that F is the maximum min-cut cost. */
vector<pair<int, int>> min_cut(int s, int t) {
	vector<pair<int, int>> ans;

	// Running Edmonds-Karp to find max flow.
	edmonds_karp(s, t);

	// Running a dfs from the source in the residual graph.
	memset(seen, false, sizeof(seen));
	dfs(s);

	for (int u = 1; u <= fnn; u++) {
		for (int i = 0; i < r[u].size(); i++) {
			int v = r[u][i].first;

			// Edge (u, v) belongs to the min-cut if u is reachable from the source but v is not.
			if (seen[u] and !seen[v]) {
				ans.push_back({u, v});
			}
		}
	}

	return ans;
}