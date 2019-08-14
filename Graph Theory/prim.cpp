#define N 100000
#define INF 0x3f3f3f3f

struct State{
	int u, v, w;

	State(){}

	State(int u, int v, int w){
		this->u = u;
		this->v = v;
		this->w = w;
	}

	bool operator < (const State &b) const{
		return w > b.w;
	}
};

int cost[N + 1];
bool in_mst[N + 1];
priority_queue<State> pq;
vector<pair<int, int>> g[N + 1]; // (Input)

/* O(V + E * Log(V)). */
void prim(int u){
	State cur;

	// Initializing.
	memset(in_mst, false, sizeof(in_mst));
	memset(cost, 0x3f, sizeof(cost));

	// Pushing initial vertex. Cost of adding the first vertex u to Minimum Spanning Tree is 0.
	cost[u] = 0;
	pq.push(State(-1, u, 0));

	// While there are vertices to visit.
	while (!pq.empty()){
		cur = pq.top();
		pq.pop();

		// Retrieving vertex u from current State.
		u = cur.v;

		// If vertex u still doesn't belong to Minimum Spanning Tree.
		if (!in_mst[u]){
			// Vertex u now belongs to Minimum Spanning Tree.
			in_mst[u] = true;

			// For every vertex v adjacent to u.
			for (int i = 0; i < (int)g[u].size(); i++){
				int v = g[u][i].first;
				int w = g[u][i].second;

				// If I've found a lower cost to add the vertex v to the Minimum Spanning Tree.
				if (!in_mst[v] and w < cost[v]){
					cost[v] = w;
					pq.push(State(u, v, cost[v]));
				}
			}
		}
	}
}