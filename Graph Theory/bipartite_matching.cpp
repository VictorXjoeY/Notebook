#define N 1000

vector<int> g[N + 1];
bool in_a[N + 1];
bool seen[N + 1];
int match[N + 1];
int n;

/* O(V + E). Returns true if it finds an augmenting path starting from vertex u. */
bool dfs(int u){
	int v, i;

	seen[u] = true;

	// Here the vertex u always belongs to Set A and the vertices v always belongs to Set B.
	for (i = 0; i < (int)g[u].size(); i++){
		v = g[u][i];

		// If vertex v from Set B is unmatched or I can find an augmenting path starting from v's match.
		if (match[v] == -1 or (!seen[match[v]] and dfs(match[v]))){
			match[v] = u;
			match[u] = v;
			return true;
		}
	}

	return false;
}

/* O(V * E). The graph can be either directed (from Set A to Set B) or undirected.
   Vertices from Set A and from Set B must all have different indexes. Vertices
   should be marked as "in_a" or not "in_a" beforehand.
   This works on ANY Bipartite Graph. */
int bipartite_matching(){
	int ans, cur, u;

	// Initializing every vertex as unmatched.
	memset(match, -1, sizeof(match));
	ans = 0;

	// This while iterates at most O(V) times (maximum possible matching).
	while (true){
		memset(seen, false, sizeof(seen));
		cur = 0;

		// Running a DFS starting from unmatched vertices from Set A.
		for (u = 1; u <= n; u++){
			if (in_a[u] and match[u] == -1 and !seen[u]){
				cur += dfs(u);
			}
		}

		// If the matching cannot be improved.
		if (!cur){
			break;
		}

		ans += cur;
	}

	return ans;
}