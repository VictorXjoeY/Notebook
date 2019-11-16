constexpr int N = 100000;

struct State {
	int u, d;

	bool operator < (const State &b) const {
		return d > b.d;
	}
};

int dist[N + 1];
bool in_spt[N + 1];
priority_queue<State> pq;
vector<pair<int, int>> g[N + 1]; // (Input)

/* O(V + E * Log(V)). */
void dijkstra(int u) {
	// Initializing.
	memset(in_spt, false, sizeof(in_spt));
	memset(dist, 0x3f, sizeof(dist));

	// Initializing and pushing source vertex. Cost of adding the first vertex u to Shortest Path Tree is 0.
	dist[u] = 0;
	pq.push({u, 0});

	// While there are vertices to visit.
	while (!pq.empty()) {
		// Retrieving vertex u from current State.
		u = pq.top().u;
		pq.pop();

		// If vertex u still doesn't belong to Shortest Path Tree.
		if (!in_spt[u]) {
			// Vertex u now belongs to Shortest Path Tree.
			in_spt[u] = true;

			// For every vertex v adjacent to u.
			for (int i = 0; i < g[u].size(); i++) {
				int v = g[u][i].first;
				int w = g[u][i].second;

				// If a better path was found to add the vertex v to the Shortest Path Tree.
				if (!in_spt[v] and dist[u] + w < dist[v]) {
					dist[v] = dist[u] + w;
					pq.push({v, dist[v]});
				}
			}
		}
	}
}
