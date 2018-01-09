#define N 100000

vector<int> g[N + 1];
vector<int> gt[N + 1];
vector<int> gs[N + 1];
vector<int> component[N + 1];
bool seen[N + 1];
int color[N + 1];
stack<int> s;
int n, m, cur;

/* O(V + E). */
void dfs1(int u){
	int v, i;

	// Marking u as visited.
	seen[u] = true;

	// For every vertex v adjacent to u.
	for (i = 0; i < (int)g[u].size(); i++){
		v = g[u][i];

		// If vertex v wasn't already visited.
		if (!seen[v]){
			dfs1(v);
		}
	}

	// Pushing u into the Stack.
	s.push(u);
}

/* O(V + E). */
void dfs2(int u){
	int v, i;

	// Vertex u belongs to current component.
	color[u] = cur;
	component[cur].push_back(u);

	// For every vertex v adjacent to u.
	for (i = 0; i < (int)gt[u].size(); i++){
		v = gt[u][i];

		// If vertex v wasn't already visited.
		if (!color[v]){
			dfs2(v);
		}
		else if (color[v] != color[u]){ // If vertex v was already visited but it belongs to another component.
			// There's an edge from v's component to u's component.
			gs[color[v]].push_back(color[u]);
		}
	}
}

/* O(V + E). */
void kosaraju(){
	int u;

	// Initializing.
	memset(seen, false, sizeof(seen));
	memset(color, 0, sizeof(color));
	cur = 0;

	// Running first DFS to fill the Stack s.
	for (u = 1; u <= n; u++){
		// If vertex u wasn't already visited.
		if (!seen[u]){
			dfs1(u);
		}
	}

	// Running second DFS to build the Strongly Connected Components.
	while (!s.empty()){
		u = s.top();
		s.pop();

		// If vertex u wasn't already visited.
		if (!color[u]){
			cur++;
			dfs2(u);
		}
	}
}