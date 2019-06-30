#define N 100000

vector<int> g[N + 1]; // (Input)
int in_degree[N + 1];
int ans[N + 1];
queue<int> q; // Could be any data structure.
int n; // (Input)

/* O(V + E) - Returns true if a topological sorting exists. */
bool kahn(){
	memset(in_degree, 0, sizeof(in_degree));

	// Counting the in degree of every vertex.
	for (int u = 1; u <= n; u++){
		for (int i = 0; i < (int)g[u].size(); i++){
			int v = g[u][i];
			in_degree[v]++;
		}
	}

	// Pushing initial vertices.
	for (int u = 1; u <= n; u++){
		if (!in_degree[u]){
			q.push(u);
		}
	}

	// Initializing the number of vertices appended to the answer.
	int k = 0;

	// While there are still vertices with in degree equals to 0.
	while (!q.empty()){
		// Retrieving next vertex u with in degree equals to 0.
		int u = q.front();
		q.pop();
		k++;

		// Appending u to the answer.
		ans[k] = u;

		// Updating the in degree of every adjacent vertex v.
		for (int i = 0; i < (int)g[u].size(); i++){
			int v = g[u][i];
			in_degree[v]--;

			if (!in_degree[v]){
				q.push(v);
			}
		}
	}

	// Returns true if every vertex was appended to the answer.
	return k == n;
}