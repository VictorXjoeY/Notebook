int dist[N + 1];

bool bellman_ford(int u){
	int i, j, v, w;

	memset(dist, 0x3f, sizeof(dist));
	dist[u] = 0;

	for (i = 0; i < n - 1; i++){
		for (u = 0; u < n; u++){
			for (j = 0; j < (int)g[u].size(); j++){
				v = g[u][j].first;
				w = g[u][j].second;

				if (dist[u] + w < dist[v]){
					dist[v] = dist[u] + w;
				}
			}
		}
	}

	for (u = 0; u < n; u++){
		for (i = 0; i < (int)g[u].size(); i++){
			v = g[u][i].first;
			w = g[u][i].second;

			if (dist[u] + w < dist[v]){
				return true;
			}
		}
	}

	return false;
}