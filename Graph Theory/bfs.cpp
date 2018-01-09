#define N 100000

vector<int> g[N + 1];
int dist[N + 1];

/* O(V + E). */
void bfs(int u){
	queue<int> q;
	int v, i;

	// Initializing.
	memset(dist, -1, sizeof(dist));
	dist[u] = 0;
	q.push(u);

	// While there are vertices to visit.
	while (!q.empty()){
		u = q.front();
		q.pop();

		// For every vertex v adjacent to u.
		for (i = 0; i < (int)g[u].size(); i++){
			v = g[u][i];

			// If vertex v wasn't already visited.
			if (dist[v] == -1){
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}
}