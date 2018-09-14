/* Conditions:
Eulerian Circuit for Undirected Graph:
	- All vertices with non-zero degree are connected.
	- All vertices have even degree.

Eulerian Path for Undirected Graph:
	- All vertices with non-zero degree are connected.
	- Zero or two vertices have odd degree and all other vertices have even degree.
	- If there are two vertices with odd degree, they are the start and end vertices.

Eulerian Circuit for Directed Graph:
	- All vertices with non-zero degree belong to the same strongly connected component.
	- In degree and out degree of every vertex is the same.

Eulerian Path for Directed Graph:
	- (Start vertex) Exactly one vertex has out degree equals to in degree plus one.
	- (End vertex) Exactly one vertex has in gree equals to out degree plus one.
	- All other vertices have in degree equals to out degree.

We can find an Eulerian Path using Hierholzer's algorithm to find Eulerian Circuit
for Directed Graphs if we add an edge from the end vertex to the start vertex. */

#define N 100000

vector<vector<int> > graph, transposed;
vector<int> g[N + 1];
bool seen[N + 1];
int indegree[N + 1];
int outdegree[N + 1];
int n;

/* O(V + E) - Visits every vertex that is reachable from u. */
void dfs(const vector<vector<int> > &cur_g, int u){
	int v, i;

	seen[u] = true;

	for (i = 0; i < (int)cur_g[u].size(); i++){
		v = cur_g[u][i];

		if (!seen[v]){
			dfs(cur_g, v);
		}
	}
}

/* O(V + E) - Returns true if there is an Euler Circuit in the graph. */
bool euler_circuit(){
	int u, v;

	// Checking degrees.
	for (u = 1; u <= n; u++){
		if (indegree[u] != outdegree[u]){
			return false;
		}
	}

	// Retrieving one possible initial vertex.
	for (u = 1; u <= n; u++){
		if (indegree[u] + outdegree[u] > 0){
			break;
		}
	}

	// If there are no edges the Euler Circuit is empty.
	if (u > n){
		return true;
	}

	// Initial vertex v.
	v = u;

	// DFS in the original graph.
	memset(seen, false, sizeof(seen));
	dfs(graph, v);

	// False if it didn't reach non-zero degree vertices.
	for (u = 1; u <= n; u++){
		if (indegree[u] + outdegree[u] > 0 and !seen[u]){
			return false;
		}
	}

	// DFS in the original graph.
	memset(seen, false, sizeof(seen));
	dfs(transposed, v);

	// False if it didn't reach non-zero degree vertices.
	for (u = 1; u <= n; u++){
		if (indegree[u] + outdegree[u] > 0 and !seen[u]){
			return false;
		}
	}

	return true;
}

/* O(V + E) - Returns the Euler Circuit starting at vertex x. If Euler Circuit does not exist, returns an empty circuit. */
vector<int> hierholzer(int x){
	vector<int> circuit;
	stack<int> path;
	int u, v, i;

	memset(indegree, 0, sizeof(indegree));
	memset(outdegree, 0, sizeof(outdegree));
	graph.resize(n + 1);
	transposed.resize(n + 1);

	// Retrieving the in degree and the out degree of each vertex and building the transposed graph.
	for (u = 1; u <= n; u++){
		outdegree[u] = g[u].size();

		for (i = 0; i < (int)g[u].size(); i++){
			v = g[u][i];
			indegree[v]++;
			graph[u].push_back(v);
			transposed[v].push_back(u);
		}
	}

	// Checking if there is an Euler Circuit.
	if (!euler_circuit()){
		// Returning an empty circuit.
		return circuit;
	}

	// Pushing first vertex.
	path.push(x);
	u = x;

	while (!path.empty()){
		// If there's remaining edge.
		if (outdegree[u]){
			// Pushing the current vertex.
			path.push(u);

			// Retrieving next vertex.
			v = graph[u].back();
			graph[u].pop_back();

			// Removing edge.
			outdegree[u]--;

			u = v;
		}
		else{
			// Pushing vertex into the circuit.
			circuit.push_back(u);

			// Backtracking.
			u = path.top();
			path.pop();
		}
	}

	reverse(circuit.begin(), circuit.end());

	return circuit;
}