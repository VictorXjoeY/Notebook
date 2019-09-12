/* Conditions:
Eulerian Circuit for Undirected Graph:
	- All vertices with non-zero degree are connected.
	- All vertices have even degree.

Eulerian Path for Undirected Graph:
	- All vertices with non-zero degree are connected.
	- Exactly two vertices have odd degree. They are the start and end vertices.
	- All other vertices have even degree.

Eulerian Circuit for Directed Graph:
	- All vertices with non-zero degree belong to the same strongly connected component.
	- In degree and out degree of every vertex is the same.

Eulerian Path for Directed Graph:
	- All vertices with non-zero degree belong to the same strongly connected component.
	- (Start vertex) Exactly one vertex has out degree equals to in degree plus one.
	- (End vertex) Exactly one vertex has in gree equals to out degree plus one.
	- All other vertices have in degree equals to out degree.

We can find an Eulerian Path using Hierholzer's algorithm to find Eulerian Circuit 
if we add an edge from the end vertex to the start vertex. 

Note that an Eulerian Circuit is also an Eulerian Path. */

#define N 100000

vector<int> g[N + 1]; // (Input)
int outdegree[N + 1];
int indegree[N + 1];
int degree[N + 1];
int n; // (Input)

/* O(V + E). */
void dfs(int u, const vector<unordered_map<int, int>> &graph, vector<bool> &seen){
	seen[u] = true;

	for (unordered_map<int, int>::const_iterator it = graph[u].begin(); it != graph[u].end(); it++){
		int v = it->first;

		if (!seen[v]){
			dfs(v, graph, seen);
		}
	}
}

/* O(V + E). */
vector<int> undirected_eulerian_circuit(){
	vector<unordered_map<int, int>> gaux;
	vector<int> circuit;
	vector<bool> seen;
	stack<int> s;

	// Retrieving the degrees and a copy of the graph.
	memset(degree, 0, sizeof(degree));
	gaux.resize(n + 1);

	for (int u = 1; u <= n; u++){
		degree[u] = g[u].size();

		for (int i = 0; i < g[u].size(); i++){
			int v = g[u][i];
			gaux[u][v]++;
		}
	}

	// Checking degrees.
	for (int u = 1; u <= n; u++){
		if (degree[u] % 2){
			return vector<int>();
		}
	}

	// Retrieving the start vertex.
	int root = 1;

	while (root <= n and degree[root] == 0){
		root++;
	}

	// No edges in this graph.
	if (root > n){
		return vector<int>();
	}

	// Checking if every vertex with non-zero degree belongs to the same component.
	seen.assign(n + 1, false);
	dfs(root, gaux, seen);

	for (int u = 1; u <= n; u++){
		if (degree[u] != 0 and !seen[u]){
			return vector<int>();
		}
	}

	// Pushing initial vertex.
	s.push(root);

	while (!s.empty()){
		int u = s.top();

		if (gaux[u].empty()){
			circuit.push_back(u);
			s.pop();
		}
		else{
			// Pushing adjacent vertex v.
			int v = gaux[u].begin()->first;
			s.push(v);

			// Removing (u, v).
			if (gaux[u][v] == 1){
				gaux[u].erase(v);
			}
			else{
				gaux[u][v]--;
			}

			// Removing (v, u).
			if (gaux[v][u] == 1){
				gaux[v].erase(u);
			}
			else{
				gaux[v][u]--;
			}
		}
	}

	return circuit;
}

/* O(V + E). */
vector<int> undirected_eulerian_path(){
	vector<unordered_map<int, int>> gaux;
	vector<int> circuit, path;
	vector<bool> seen;
	stack<int> s;

	// Retrieving the degrees and a copy of the graph.
	memset(degree, 0, sizeof(degree));
	gaux.resize(n + 1);

	for (int u = 1; u <= n; u++){
		degree[u] = g[u].size();

		for (int i = 0; i < g[u].size(); i++){
			int v = g[u][i];
			gaux[u][v]++;
		}
	}

	// Retrieving start vertex and end vertex.
	int x = -1;
	int y = -1;

	for (int u = 1; u <= n; u++){
		if (degree[u] % 2){
			if (x == -1){
				x = u;
			}
			else{
				y = u;
			}
		}
	}

	if (x != -1 and y != -1){ // No circuit but path might exist.
		// Adding an edge between the end vertex and the start vertex.
		gaux[x][y]++;
		gaux[y][x]++;
		degree[x]++;
		degree[y]++;
	}

	// Checking degrees.
	for (int u = 1; u <= n; u++){
		if (degree[u] % 2){
			return vector<int>();
		}
	}

	// Retrieving the start vertex.
	int root = 1;

	while (root <= n and degree[root] == 0){
		root++;
	}

	// No edges in this graph.
	if (root > n){
		return vector<int>();
	}

	// Checking if every vertex with non-zero degree belongs to the same component.
	seen.assign(n + 1, false);
	dfs(root, gaux, seen);

	for (int u = 1; u <= n; u++){
		if (degree[u] != 0 and !seen[u]){
			return vector<int>();
		}
	}

	// Pushing initial vertex.
	s.push(root);

	while (!s.empty()){
		int u = s.top();

		if (gaux[u].empty()){
			circuit.push_back(u);
			s.pop();
		}
		else{
			// Pushing adjacent vertex v.
			int v = gaux[u].begin()->first;
			s.push(v);

			// Removing (u, v).
			if (gaux[u][v] == 1){
				gaux[u].erase(v);
			}
			else{
				gaux[u][v]--;
			}

			// Removing (v, u).
			if (gaux[v][u] == 1){
				gaux[v].erase(u);
			}
			else{
				gaux[v][u]--;
			}
		}
	}

	// If an edge was artificially inserted.
	if (x != -1 and y != -1){
		// Removing extra edge.
		for (int i = 1; i < circuit.size(); i++){ // For each edge.
			if ((circuit[i - 1] == y and circuit[i] == x) or (circuit[i - 1] == x and circuit[i] == y)){ // Found the edge artificially inserted.
				for (int j = i; j < circuit.size(); j++){
					path.push_back(circuit[j]);
				}

				// Ignoring first vertex of the circuit because it is equal to the last vertex of the circuit.
				for (int j = 1; j <= i - 1; j++){
					path.push_back(circuit[j]);
				}

				break;
			}
		}

		return path;
	}

	return circuit;
}

/* O(V + E). */
void dfs(int u, const vector<vector<int>> &graph, vector<bool> &seen){
	seen[u] = true;

	for (int i = 0; i < graph[u].size(); i++){
		int v = graph[u][i];

		if (!seen[v]){
			dfs(v, graph, seen);
		}
	}
}

/* O(V + E). */
vector<int> directed_eulerian_circuit(){
	vector<vector<int>> gaux, gt;
	vector<bool> seen, seent;
	vector<int> circuit;
	stack<int> s;

	// Retrieving indegree, outdegree, a copy of the graph and the transposed graph.
	memset(indegree, 0, sizeof(indegree));
	gaux.resize(n + 1);
	gt.resize(n + 1);

	for (int u = 1; u <= n; u++){
		outdegree[u] = g[u].size();

		for (int i = 0; i < g[u].size(); i++){
			int v = g[u][i];
			indegree[v]++;

			gaux[u].push_back(v);
			gt[v].push_back(u);
		}
	}

	// Checking degrees.
	for (int u = 1; u <= n; u++){
		if (indegree[u] != outdegree[u]){
			return vector<int>();
		}
	}

	// Retrieving the start vertex.
	int root = 1;

	while (root <= n and outdegree[root] == 0){
		root++;
	}

	// No edges in this graph.
	if (root > n){
		return vector<int>();
	}

	// Checking if every vertex with non-zero degree belongs to the same strongly connected component.
	seen.assign(n + 1, false);
	seent.assign(n + 1, false);
	dfs(root, gaux, seen);
	dfs(root, gt, seent);

	for (int u = 1; u <= n; u++){
		if (indegree[u] + outdegree[u] > 0 and (!seen[u] or !seent[u])){
			return vector<int>();
		}
	}

	// Pushing initial vertex.
	s.push(root);
	int u = root;

	while (!s.empty()){
		// If there's a remaining edge.
		if (!gaux[u].empty()){
			// Pushing the current vertex.
			s.push(u);

			// Retrieving the next vertex.
			int v = gaux[u].back();
			gaux[u].pop_back();
			u = v;
		}
		else{
			// Pushing the current vertex into the circuit.
			circuit.push_back(u);

			// Backtracking.
			u = s.top();
			s.pop();
		}
	}

	// Reversing the circuit that was found.
	reverse(circuit.begin(), circuit.end());

	return circuit;
}

/* O(V + E). */
vector<int> directed_eulerian_path(){
	vector<vector<int>> gaux, gt;
	vector<int> path, circuit;
	vector<bool> seen, seent;
	stack<int> s;

	// Retrieving indegree, outdegree, a copy of the graph and the transposed graph.
	memset(indegree, 0, sizeof(indegree));
	gaux.resize(n + 1);
	gt.resize(n + 1);

	for (int u = 1; u <= n; u++){
		outdegree[u] = g[u].size();

		for (int i = 0; i < g[u].size(); i++){
			int v = g[u][i];
			indegree[v]++;

			gaux[u].push_back(v);
			gt[v].push_back(u);
		}
	}

	// Retrieving start vertex and end vertex.
	int x = -1;
	int y = -1;

	for (int u = 1; u <= n; u++){
		if (outdegree[u] == indegree[u] + 1){
			x = u;
		}

		if (indegree[u] == outdegree[u] + 1){
			y = u;
		}
	}

	if (x != -1 and y != -1){ // No circuit but a path might exist.
		// Adding an edge between the end vertex and the start vertex.
		gaux[y].push_back(x);
		gt[x].push_back(y);
		outdegree[y]++;
		indegree[x]++;
	}

	// Checking degrees.
	for (int u = 1; u <= n; u++){
		if (indegree[u] != outdegree[u]){
			return vector<int>();
		}
	}

	// Retrieving the start vertex.
	int root = 1;

	while (root <= n and outdegree[root] == 0){
		root++;
	}

	// No edges in this graph.
	if (root > n){
		return vector<int>();
	}

	// Checking if every vertex with non-zero degree belongs to the same strongly connected component.
	seen.assign(n + 1, false);
	seent.assign(n + 1, false);
	dfs(root, gaux, seen);
	dfs(root, gt, seent);

	for (int u = 1; u <= n; u++){
		if (indegree[u] + outdegree[u] > 0 and (!seen[u] or !seent[u])){
			return vector<int>();
		}
	}

	// Pushing initial vertex.
	s.push(root);
	int u = root;

	while (!s.empty()){
		// If there's a remaining edge.
		if (!gaux[u].empty()){
			// Pushing the current vertex.
			s.push(u);

			// Retrieving the next vertex.
			int v = gaux[u].back();
			gaux[u].pop_back();
			u = v;
		}
		else{
			// Pushing the current vertex into the circuit.
			circuit.push_back(u);

			// Backtracking.
			u = s.top();
			s.pop();
		}
	}

	// Reversing the circuit that was found.
	reverse(circuit.begin(), circuit.end());

	// If an edge was artificially inserted.
	if (x != -1 and y != -1){
		// Removing extra edge.
		for (int i = 1; i < circuit.size(); i++){ // For each edge.
			if (circuit[i - 1] == y and circuit[i] == x){ // Found the edge artificially inserted.
				// Starting from x.
				for (int j = i; j < circuit.size(); j++){
					path.push_back(circuit[j]);
				}

				// Ending at y. Ignoring first vertex of the circuit because it is equal to the last vertex of the circuit.
				for (int j = 1; j <= i - 1; j++){
					path.push_back(circuit[j]);
				}

				break;
			}
		}

		return path;
	}

	return circuit;
}