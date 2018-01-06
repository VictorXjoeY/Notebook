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

void dijkstra(int u){
	int i, v, w;
	State cur;

	memset(in_spt, false, sizeof(in_spt));
	memset(dist, 0x3f, sizeof(dist));

	dist[u] = 0;
	pq.push(State(u, 0));

	while (!pq.empty()){
		cur = pq.top();
		pq.pop();

		u = cur.u;

		if (!in_spt[u]){
			in_spt[u] = true;

			for (i = 0; i < (int)g[u].size(); i++){
				v = g[u][i].first;
				w = g[u][i].second;

				if (dist[u] + w < dist[v]){
					dist[v] = dist[u] + w;
					pq.push(State(v, dist[v]));
				}
			}
		}
	}
}