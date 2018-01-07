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
vector<pair<int, int> > g[N + 1];

void prim(int u){
	int i, v, w;
	State cur;

	memset(in_mst, false, sizeof(in_mst));
	memset(cost, 0x3f, sizeof(cost));

	cost[u] = 0;
	pq.push(State(-1, u, 0));

	while (!pq.empty()){
		cur = pq.top();
		pq.pop();

		u = cur.v;

		if (!in_mst[u]){
			in_mst[u] = true;

			for (i = 0; i < (int)g[u].size(); i++){
				v = g[u][i].first;
				w = g[u][i].second;

				if (!in_mst[v] and w < cost[v]){
					cost[v] = w;
					pq.push(State(u, v, cost[v]));
				}
			}
		}
	}
}