#define N 300

vector<pair<int, int> > g[N + 1];
int dist[N + 1][N + 1];
int n;

/* O(V^3). */
void floyd_warshall(){
	int u, v, w, i, j, k;

	// Initializing.
	memset(dist, 0x3f, sizeof(dist));

	// Filling distance matrix with the edges.
	for (u = 1; u <= n; u++){
		dist[u][u] = 0;

		for (i = 0; i < (int)g[u].size(); i++){
			v = g[u][i].first;
			w = g[u][i].second;

			dist[u][v] = w;
		}
	}

	// For every intermediate vertex k.
	for (k = 1; k <= n; k++){
		// For every starting vertex i.
		for (i = 1; i <= n; i++){
			// For every ending vertex j.
			for (j = 1; j <= n; j++){
				// If there is a better path using k as intermediate vertex.
				if (dist[i][k] + dist[k][j] < dist[i][j]){
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}
}