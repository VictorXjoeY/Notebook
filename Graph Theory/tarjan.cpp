#define N 100000

vector<pair<int, int>> bridge;
bool ap[N + 1];

vector<int> g[N + 1]; // (Input)
bool seen[N + 1];
int parent[N + 1];
int disc[N + 1];
int low[N + 1];
int timer;
int n; // (Input)

/* O(V + E). */
void dfs(int u){
	// Marking u as visited.
	seen[u] = true;
	low[u] = disc[u] = ++timer;
	int child = 0;

	// For every vertex v adjacent to u.
	for (int i = 0; i < (int)g[u].size(); i++){
		int v = g[u][i];

		// If vertex v wasn't already visited.
		if (!seen[v]){
			parent[v] = u;
			child++;

			dfs(v);

			low[u] = min(low[u], low[v]);

			// If u is root and has 2 or more children in the DFS Tree or u is not root and low[v] >= disc[u].
			if ((!parent[u] and child >= 2) or (parent[u] and low[v] >= disc[u])){
				// Vertex u is an Articulation Point and removing it will disconnect the subtree rooted at v.
				ap[u] = true;
			}

			// If can't reach u or above from v's subtree using a back edge.
			if (low[v] > disc[u]){
				// Edge (u, v) is a bridge.
				bridge.push_back(make_pair(u, v));
			}
		}
		else if (v != parent[u]){
			// I've found a back edge, updating low[u].
			low[u] = min(low[u], disc[v]);
		}
	}
}

/* O(V + E). */
void tarjan(){
	// Initializing.
	memset(seen, false, sizeof(seen));
	memset(ap, false, sizeof(ap));
	parent[1] = 0;
	timer = 0;

	// Running the DFS.
	for (int u = 1; u <= n; u++){
		if (!seen[u]){
			dfs(u);
		}
	}
}
