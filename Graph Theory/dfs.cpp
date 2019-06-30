#define N 100000

vector<int> g[N + 1]; // (Input)
bool seen[N + 1];

/* O(V + E). */
void dfs(int u){
	// Marking u as visited.
	seen[u] = true;

	// For every vertex v adjacent to u.
	for (int i = 0; i < (int)g[u].size(); i++){
		int v = g[u][i];

		// If vertex v wasn't already visited.
		if (!seen[v]){
			dfs(v);
		}
	}
}