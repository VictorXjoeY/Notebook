constexpr int INF = 0x3f3f3f3f;
constexpr int N = 100000;

struct State{
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
	State cur;

	// Initializing.
	memset(in_spt, false, sizeof(in_spt));
	memset(dist, 0x3f, sizeof(dist));

	// Pushing initial vertex.
	dist[u] = 0;
	pq.push({u, 0});

	// While there are vertices to visit.
	while (!pq.empty()) {
		cur = pq.top();
		pq.pop();

		// Retrieving vertex u from current State.
		u = cur.u;

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
