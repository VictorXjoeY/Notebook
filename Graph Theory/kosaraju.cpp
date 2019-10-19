constexpr int N = 100000;

vector<int> g[N + 1]; // (Input)
vector<int> gt[N + 1]; // (Input)
vector<int> gs[N + 1]; // This graph will be topologically sorted after running Kosaraju's Algorithm.
vector<int> component[N + 1]; // component[c] stores which vertices belong to the component c.
bool seen[N + 1];
int color[N + 1]; // color[u] stores which component u belongs to.
stack<int> s;
int nc; // Stores the number of components.
int n; // (Input)

/* O(V + E). */
void dfs1(int u){
	// Marking u as visited.
	seen[u] = true;

	// For every vertex v adjacent to u.
	for (int i = 0; i < (int)g[u].size(); i++){
		int v = g[u][i];

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
	// Vertex u belongs to current component.
	color[u] = nc;
	component[nc].push_back(u);

	// For every vertex v adjacent to u.
	for (int i = 0; i < (int)gt[u].size(); i++){
		int v = gt[u][i];

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
	// Initializing.
	memset(seen, false, sizeof(seen));
	memset(color, 0, sizeof(color));
	nc = 0;

	// Running first DFS to fill the Stack s.
	for (int u = 1; u <= n; u++){
		// If vertex u wasn't already visited.
		if (!seen[u]){
			dfs1(u);
		}
	}

	// Running second DFS to build the Strongly Connected Components.
	while (!s.empty()){
		int u = s.top();
		s.pop();

		// If vertex u wasn't already visited.
		if (!color[u]){
			nc++;
			dfs2(u);
		}
	}
}