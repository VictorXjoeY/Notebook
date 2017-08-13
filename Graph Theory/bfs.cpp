int dist[N + 1];

void bfs(int u){
	queue<int> q;
	int v, i;

	memset(dist, -1, sizeof(dist));
	dist[u] = 0;
	q.push(u);

	while (!q.empty()){
		u = q.front();
		q.pop();

		for (i = 0; i < (int)g[u].size(); i++){
			v = g[u][i];

			if (dist[v] == -1){
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}
}