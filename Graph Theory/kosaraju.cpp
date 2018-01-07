#define N 100000

vector<int> g[N + 1];
vector<int> gt[N + 1];
vector<int> gs[N + 1];
vector<int> component[N + 1];
bool seen[N + 1];
int color[N + 1];
stack<int> s;
int n, m, cur;

void dfs1(int u){
	int v, i;

	seen[u] = true;

	for (i = 0; i < (int)g[u].size(); i++){
		v = g[u][i];

		if (!seen[v]){
			dfs1(v);
		}
	}

	s.push(u);
}

void dfs2(int u){
	int v, i;

	color[u] = cur;
	component[color[u]].push_back(u);

	for (i = 0; i < (int)gt[u].size(); i++){
		v = gt[u][i];

		if (!color[v]){
			dfs2(v);
		}
		else if (color[v] != color[u]){
			gs[color[v]].push_back(color[u]);
		}
	}
}

void kosaraju(){
	int u;

	// Initializing.
	memset(seen, false, sizeof(seen));
	memset(color, 0, sizeof(color));
	cur = 0;

	// Running first DFS to fill the Stack.
	for (u = 1; u <= n; u++){
		if (!seen[u]){
			dfs1(u);
		}
	}

	// Running second DFS to build the Strongly Connected Components.
	while (!s.empty()){
		u = s.top();
		s.pop();

		if (!color[u]){
			cur++;
			dfs2(u);
		}
	}
}