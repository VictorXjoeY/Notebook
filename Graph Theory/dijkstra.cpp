#define N 100000
#define INF 0x3f3f3f3f

struct State{
	int u, d;

	State(){}

	State(int u, int d){
		this->u = u;
		this->d = d;
	}

	bool operator < (const State &b) const{
		return d > b.d;
	}
};

int dist[N + 1];
bool in_spt[N + 1];
priority_queue<State> pq;
vector<pair<int, int> > g[N + 1];

/* O(V + E * log(V)). */
void dijkstra(int u){
	int v, w, i;
	State cur;

	// Initializing.
	memset(in_spt, false, sizeof(in_spt));
	memset(dist, 0x3f, sizeof(dist));

	// Pushing initial vertex.
	dist[u] = 0;
	pq.push(State(u, 0));

	// While there are vertices to visit.
	while (!pq.empty()){
		cur = pq.top();
		pq.pop();

		// Retrieving vertex u from current State.
		u = cur.u;

		// If vertex u still doesn't belong to Shortest Path Tree.
		if (!in_spt[u]){
			// Vertex u now belongs to Shortest Path Tree.
			in_spt[u] = true;

			// For every vertex v adjacent to u.
			for (i = 0; i < (int)g[u].size(); i++){
				v = g[u][i].first;
				w = g[u][i].second;

				// If a better path was found to add the vertex v to the Shortest Path Tree.
				if (!in_spt[v] and dist[u] + w < dist[v]){
					dist[v] = dist[u] + w;
					pq.push(State(v, dist[v]));
				}
			}
		}
	}
}
