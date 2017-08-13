bool seen[N + 1];
int d[N + 1];
int f[N + 1];
int p[N + 1];
int tempo;

void dfs(int u){
	int v, i;

	seen[u] = true;
	d[u] = tempo;
	tempo++;

	for (i = 0; i < (int)g[u].size(); i++){
		v = g[u][i];

		if (!seen[v]){
			p[v] = u;
			dfs(v);
		}
	}

	f[u] = tempo;
	tempo++;
}