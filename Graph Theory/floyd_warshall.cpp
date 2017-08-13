int dist[N + 1][N + 1];
int n;

void floyd_warshall(){
	int i, j, k;

	memset(dist, 0x3f, sizeof(dist));

	for (i = 1; i <= n; i++){
		dist[i][i] = 0;

		for (j = 0; j < (int)g[i].size(); j++){
			dist[i][g[i][j]] = 1;
		}
	}

	for (i = 1; i <= n; i++){
		for (j = 1; j <= n; j++){
			for (k = 1; k <= n; k++){
				if (dist[j][i] + dist[i][k] < dist[j][k]){
					dist[j][k] = dist[j][i] + dist[i][k];
				}
			}
		}
	}
}