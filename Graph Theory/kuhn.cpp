/* 
Konig's Theorem states that: "In any bipartite graph, the number of edges
in a maximum matching equals the number of vertices in a minimum vertex cover."

Building the Minimum Vertex Cover:
	- Make matching edges from right to left (B to A).
	- Make non-matching edges from left to right (A to B).
	- Run a DFS from vertices that don't belong to the matching.
	- The Minimum Vertex Cover will be the vertices from the left (A) that WERE NOT visited
	and the vertices from the right (B) that WERE visited.

The complement of a Vertex Cover is an Independent Set, therefore a
Maximum Independent Set is the complement of a Minimum Vertex Cover.
*/

constexpr int N = 1000;

vector<int> g[N + 1]; // (Input)
bool in_a[N + 1];
bool seen[N + 1];
int match[N + 1];
int n; // (Input)

/* O(V + E). Returns true if it finds an augmenting path starting from vertex u. */
bool dfs(int u){
	seen[u] = true;

	// Here the vertex u always belongs to Set A and the vertices v always belongs to Set B.
	for (int i = 0; i < g[u].size(); i++){
		int v = g[u][i];

		// If vertex v from Set B is unmatched or I can find an augmenting path starting from v's match.
		if (match[v] == -1 or (!seen[match[v]] and dfs(match[v]))){
			match[v] = u;
			match[u] = v;
			return true;
		}
	}

	return false;
}

/* O(V + E). Partitions the vertices in 2 sets by bicoloring. */
void bicolor(int u, bool color){
	seen[u] = true;
	in_a[u] = color;

	for (int i = 0; i < g[u].size(); i++){
		int v = g[u][i];

		if (!seen[v]){
			bicolor(v, !color);
		}
		else if (in_a[u] == in_a[v]){
			// Graph is not Bipartite.
			assert(false);
		}
	}
}

/* O(V * E). The graph can be either directed (from Set A to Set B) or undirected.
   Vertices from Set A and from Set B must all have different indexes.
   This works on ANY Bipartite Graph. */
int kuhn(){
	int ans, cur;

	memset(seen, false, sizeof(seen));

	// Filling the "in_a" array.
	for (int u = 1; u <= n; u++){
		if (!seen[u]){
			bicolor(u, true);
		}
	}

	// Initializing every vertex as unmatched.
	memset(match, -1, sizeof(match));
	ans = 0;

	// This while iterates at most O(V) times (maximum possible matching).
	while (true){
		memset(seen, false, sizeof(seen));
		cur = 0;

		// Running a DFS starting from unmatched vertices from Set A.
		for (int u = 1; u <= n; u++){
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