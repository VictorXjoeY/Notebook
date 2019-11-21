constexpr int N = 100000;
constexpr int M = 100000;

vector<int> g[2 * N + 2]; // Implication graph.
vector<int> gt[2 * N + 2]; // Transposed graph.
bool seen[2 * N + 2];
int color[2 * N + 2]; // color[u] stores which component u belongs to.
stack<int> s;
int ans[N + 1]; // (Output) Final assignment.
pair<int, int> clause[M + 1]; // (Input) Each clause as a pair (a, b). If (-a, b) is given that means that the clause is (!a or b).
int n, m; // (Input) Number of variables and number of clauses.
int nc; // Stores the number of components.

/* O(V + E). */
void dfs1(int u) {
	// Marking u as visited.
	seen[u] = true;

	// For every vertex v adjacent to u.
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];

		// If vertex v wasn't already visited.
		if (!seen[v]) {
			dfs1(v);
		}
	}

	// Pushing u into the Stack.
	s.push(u);
}

/* O(V + E). */
void dfs2(int u) {
	// Vertex u belongs to current component.
	color[u] = nc;

	// For every vertex v adjacent to u.
	for (int i = 0; i < gt[u].size(); i++) {
		int v = gt[u][i];

		// If vertex v wasn't already visited.
		if (!color[v]) {
			dfs2(v);
		}
	}
}

/* O(V + E). */
void kosaraju() {
	// Clearing.
	for (int u = 1; u <= n; u++) {
		gt[u].clear();
	}

	memset(seen, false, sizeof(seen));
	memset(color, 0, sizeof(color));
	nc = 0;

	// Building the transposed graph.
	for (int u = 1; u <= n; u++) {
		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];
			gt[v].push_back(u);
		}
	}

	// Running first DFS to fill the Stack s.
	for (int u = 1; u <= n; u++) {
		// If vertex u wasn't already visited.
		if (!seen[u]) {
			dfs1(u);
		}
	}

	// Running second DFS to build the Strongly Connected Components.
	while (!s.empty()) {
		int u = s.top();
		s.pop();

		// If vertex u wasn't already visited.
		if (!color[u]) {
			nc++;
			dfs2(u);
		}
	}
}

/* O(N + M) - Such that N is the number of variables and M is the number of clauses.
   Returns true if there's a possible assignment to all variables and false otherwise. */
bool two_sat() {
	// Clearing.
	for (int a = 1; a <= n; a++) {
		g[a + (n + 1)].clear();
		g[(-a) + (n + 1)].clear();
	}

	// For each clause (a or b), creating edges !a -> b and !b -> a.
	for (int i = 1; i <= m; i++) {
		int a = clause[i].first;
		int b = clause[i].second;

		// Adding (n + 1) as an offset.
		g[(-a) + (n + 1)].push_back(b + (n + 1));
		g[(-b) + (n + 1)].push_back(a + (n + 1));
	}

	// Running Kosaraju on the implication graph. The resulting components will be topologically sorted.
	n = 2 * n + 1;
	kosaraju();
	n = (n - 1) / 2;

	// Assigning a value to each variable according to the position on the resulting topologically sorted graph.
	for (int a = 1; a <= n; a++) {
		if (color[a + (n + 1)] == color[(-a) + (n + 1)]) { // Contradiction a implies !a and !a implies a.
			return false;
		}

		ans[a] = color[a + (n + 1)] > color[(-a) + (n + 1)];
	}

	// No variable assignment led to a contradiction.
	return true;
}