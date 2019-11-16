constexpr int N = 100000;

struct State {
	int u, v, w;

	bool operator < (const State &b) const {
		return w > b.w;
	}
};

vector<pair<int, int>> g[N + 1]; // (Input)
priority_queue<State> pq;
bool in_mst[N + 1];
int cost[N + 1];

/* O(V + E * Log(V)). */
void prim(int u) {
	// Initializing.
	memset(in_mst, false, sizeof(in_mst));
	memset(cost, 0x3f, sizeof(cost));

	// Initializing and pushing source vertex. Cost of adding the first vertex u to Minimum Spanning Tree is 0.
	cost[u] = 0;
	pq.push({-1, u, 0});

	// While there are vertices to visit.
	while (!pq.empty()) {
		// Retrieving vertex u from current State.
		u = pq.top().v;
		pq.pop();

		// If vertex u still doesn't belong to Minimum Spanning Tree.
		if (!in_mst[u]) {
			// Vertex u now belongs to Minimum Spanning Tree.
			in_mst[u] = true;

			// For every vertex v adjacent to u.
			for (int i = 0; i < g[u].size(); i++) {
				int v = g[u][i].first;
				int w = g[u][i].second;

				// If a lower cost was found to add the vertex v to the Minimum Spanning Tree.
				if (!in_mst[v] and w < cost[v]) {
					cost[v] = w;
					pq.push({u, v, cost[v]});
				}
			}
		}
	}
}