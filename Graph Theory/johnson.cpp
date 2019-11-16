constexpr int N = 1000;

struct State {
	int u, d;

	bool operator < (const State &b) const {
		return d > b.d;
	}
};

vector<pair<int, int>> g[N + 1]; // (Input)
priority_queue<State> pq;
bool in_spt[N + 1][N + 1];
int dist[N + 1][N + 1];
bool in_queue[N + 1];
int h[N + 1];
int n; // (Input)

/* O(V + E * Log(V)). */
void dijkstra(int s) {
	// Pushing initial vertex.
	dist[s][s] = 0;
	pq.push({s, 0});

	// While there are vertices to visit.
	while (!pq.empty()) {
		// Retrieving vertex u from current State.
		int u = pq.top().u;
		pq.pop();

		// If vertex u still doesn't belong to Shortest Path Tree.
		if (!in_spt[s][u]) {
			// Vertex u now belongs to Shortest Path Tree.
			in_spt[s][u] = true;

			// For every vertex v adjacent to u.
			for (int i = 0; i < g[u].size(); i++) {
				int v = g[u][i].first;
				int w = g[u][i].second;

				// If a better path was found to add the vertex v to the Shortest Path Tree.
				if (!in_spt[s][v] and dist[s][u] + w < dist[s][v]) {
					dist[s][v] = dist[s][u] + w;
					pq.push({v, dist[s][v]});
				}
			}
		}
	}
}

/* O(V * E) - Returns true if there is a negative cycle reachable from u.
   Connect an extra vertex 0 to every other vertex with weight -1 and call spfa(0) to detect negative cycles in the entire graph. */
bool spfa(int u) {
	vector<int> cur;
	queue<int> q;

	// Clearing.
	memset(in_queue, false, sizeof(in_queue));
	memset(h, 0x3f, sizeof(h));

	// Initializing.
	h[u] = 0;
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
				if (h[u] + w < h[v]) {
					h[v] = h[u] + w;

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

/* O(V * E * Log(V)) - Returns true if there's a negative cycle in the graph. */
bool johnson() {
	// Adding an extra vertex connected to every other vertex with weight 0.
	for (int u = 1; u <= n; u++) {
		g[0].push_back({u, 0});
	}

	// Running SPFA to find distance h[u] between 0 and u.
	if (spfa(0)) { // If a negative cycle was found.
		return true;
	}

	// Updating every edge (u, v) with weight w to w + h[u] - h[v].
	for (int u = 1; u <= n; u++) {
		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i].first;
			g[u][i].second += h[u] - h[v];
		}
	}

	// Clearing.
	memset(in_spt, false, sizeof(in_spt));
	memset(dist, 0x3f, sizeof(dist));

	// Running Dijkstra for each vertex.
	for (int u = 1; u <= n; u++) {
		dijkstra(u);
	}

	// Adjusting the weights back.
	for (int u = 1; u <= n; u++) {
		for (int v = 1; v <= n; v++) {
			dist[u][v] += h[v] - h[u];
		}
	}

	// No negative cycle was found.
	return false;
}
