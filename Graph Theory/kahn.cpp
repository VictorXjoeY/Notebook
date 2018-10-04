#define N 100000

vector<int> g[N + 1];
int in_degree[N + 1];
int ans[N + 1];
queue<int> q; // Could be any data structure.
int n;

/* O(V + E). Returns true if a topological sorting exists. */
bool kahn(){
	int u, v, i, k;

	memset(in_degree, 0, sizeof(in_degree));

	// Counting the in degree of every vertex.
	for (u = 1; u <= n; u++){
		for (i = 0; i < (int)g[u].size(); i++){
			v = g[u][i];
			in_degree[v]++;
		}
	}

	// Pushing initial vertices.
	for (u = 1; u <= n; u++){
		if (!in_degree[u]){
			q.push(u);
		}
	}

	// Initializing the number of vertices appended to the answer.
	k = 0;

	// While there are still vertices with in degree equals to 0.
	while (!q.empty()){
		// Retrieving next vertex u with in degree equals to 0.
		u = q.front();
		q.pop();
		k++;

		// Appending u to the answer.
		ans[k] = u;

		// Updating the in degree of every adjacent vertex v.
		for (i = 0; i < (int)g[u].size(); i++){
			v = g[u][i];
			in_degree[v]--;

			if (!in_degree[v]){
				q.push(v);
			}
		}
	}

	// Returns true if every vertex was appended to the answer.
	return k == n;
}