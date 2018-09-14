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

/* O(V + E) - Returns the Euler Circuit starting at vertex x. If Euler Circuit does not exist, returns an empty circuit. */
vector<int> hierholzer(const vector<vector<int> > &g, int n, int x){
	vector<int> outdegree, circuit;
	vector<vector<int> > graph;
	stack<int> path;
	int u, v, i;

	outdegree.assign(n + 1, 0);
	graph.resize(n + 1);

	// Retrieving the out degree of each vertex and building a copy of the graph.
	for (u = 1; u <= n; u++){
		outdegree[u] = g[u].size();

		for (i = 0; i < (int)g[u].size(); i++){
			v = g[u][i];
			graph[u].push_back(v);
		}
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

	// Reversing found circuit.
	reverse(circuit.begin(), circuit.end());

	return circuit;
}

/* O(V + E) - Visits every vertex that is reachable from u. */
void dfs(const vector<vector<int> > &g, vector<bool> &seen, int u){
	int v, i;

	seen[u] = true;

	for (i = 0; i < (int)g[u].size(); i++){
		v = g[u][i];

		if (!seen[v]){
			dfs(g, seen, v);
		}
	}
}

/* O(V + E) - Checks wheter there is an Euler Circuit in the graph g. */
bool has_euler_circuit(const vector<vector<int> > &g, int n){
	vector<int> indegree, outdegree;
	vector<vector<int> > gt;
	vector<bool> seen, seent;
	int x, u, v, i;

	// Initializing.
	indegree.assign(n + 1, 0);
	outdegree.assign(n + 1, 0);
	gt.resize(n + 1);

	// Retrieving the in degree and the out degree of each vertex and building the transposed graph.
	for (u = 1; u <= n; u++){
		outdegree[u] = g[u].size();

		for (i = 0; i < (int)g[u].size(); i++){
			v = g[u][i];

			indegree[v]++;
			gt[v].push_back(u);
		}
	}

	// Checking degrees.
	for (u = 1; u <= n; u++){
		if (indegree[u] != outdegree[u]){
			return false;
		}
	}

	// Retrieving one possible initial vertex.
	for (u = 1; u <= n; u++){
		if (indegree[u] + outdegree[u] > 0){
			x = u;
			break;
		}
	}

	// If there are no edges the Euler Circuit is empty.
	if (u > n){
		return true;
	}

	// DFS from x in the original graph and in the transposed graph.
	seen.assign(n + 1, false);
	dfs(g, seen, x);
	seent.assign(n + 1, false);
	dfs(gt, seent, x);

	// False if it didn't reach non-zero degree vertices in any of the DFSs.
	for (u = 1; u <= n; u++){
		if (indegree[u] + outdegree[u] > 0 and (!seen[u] or !seent[u])){
			return false;
		}
	}

	return true;
}

/* O(V + E) - Checks wheter there is an Euler Path in the graph g but NOT an Euler Circuit. */
bool has_euler_path(const vector<vector<int> > &g, int n){
	vector<int> indegree, outdegree;
	vector<vector<int> > gaux;
	int x, y, u, v, i;

	// Initializing.
	indegree.assign(n + 1, 0);
	outdegree.assign(n + 1, 0);
	gaux.resize(n + 1);

	// Retrieving the in degree and the out degree of each vertex and building a copy of the graph.
	for (u = 1; u <= n; u++){
		outdegree[u] = g[u].size();

		for (i = 0; i < (int)g[u].size(); i++){
			v = g[u][i];

			indegree[v]++;
			gaux[u].push_back(v);
		}
	}

	x = y = -1;

	// Retrieving (possible) start and end vertices.
	for (u = 1; u <= n; u++){
		if (outdegree[u] == indegree[u] + 1){
			if (x == -1){
				x = u;
			}
			else{
				// Can't have 2 start vertices.
				return false;
			}
		}

		if (indegree[u] == outdegree[u] + 1){
			if (y == -1){
				y = u;
			}
			else{
				// Can't have 2 end vertices.
				return false;
			}
		}
	}

	// No start or end vertex.
	if (x == -1 or y == -1){
		return false;
	}

	// Adding an edge between the end vertex and the start vertex.
	gaux[y].push_back(x);

	// Now there should be an euler circuit.
	return has_euler_circuit(gaux, n);
}

/* Returns an Euler Circuit starting from vertex x. You should pass a start vertex x that has non-zero degree. Graph must have an Euler Circuit. */
vector<int> euler_circuit(const vector<vector<int> > &g, int n, int x){
	return hierholzer(g, n, x);
}

/* Returns an Euler Path. Graph must have an Euler Path. */
vector<int> euler_path(const vector<vector<int> > &g, int n){
	vector<int> indegree, outdegree, circuit, path;
	vector<vector<int> > gaux;
	int x, y, u, v, i, j;

	// Initializing.
	indegree.assign(n + 1, 0);
	outdegree.assign(n + 1, 0);
	gaux.resize(n + 1);

	// Retrieving the in degree and the out degree of each vertex and building a copy of the graph.
	for (u = 1; u <= n; u++){
		outdegree[u] = g[u].size();

		for (i = 0; i < (int)g[u].size(); i++){
			v = g[u][i];

			indegree[v]++;
			gaux[u].push_back(v);
		}
	}

	x = y = -1;

	// Retrieving (possible) start and end vertices.
	for (u = 1; u <= n; u++){
		if (outdegree[u] == indegree[u] + 1){
			if (x == -1){
				x = u;
			}
		}

		if (indegree[u] == outdegree[u] + 1){
			if (y == -1){
				y = u;
			}
		}
	}

	// Adding an edge between the end vertex and the start vertex.
	gaux[y].push_back(x);

	// Retrieving an Euler Circuit starting from vertex x.
	circuit = euler_circuit(gaux, n, x);

	// Removing the extra edge and filling up the path.
	for (i = 0; i < (int)circuit.size() - 1; i++){ // For each edge.
		if (circuit[i] == y and circuit[i + 1] == x){ // Found the edge artificially inserted.
			// Path begins from x. Ignores the last vertex because it was only there because of the circuit.
			for (j = i + 1; j < (int)circuit.size() - 1; j++){
				path.push_back(circuit[j]);
			}

			// Continues the path up until y.
			for (j = 0; j <= i; j++){
				path.push_back(circuit[j]);
			}

			break;
		}
	}

	return path;
}