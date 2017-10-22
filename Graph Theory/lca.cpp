int ancestor[N + 1][L + 1];
int parent[N + 1];
int depth[N + 1];

void lca_init(){
	int i, j;

	memset(ancestor, -1, sizeof(ancestor));

	for (i = 1; i <= N; i++){
		ancestor[i][0] = parent[i];
	}

	for (j = 1; j <= L; j++){
		for (i = 1; i <= N; i++){
			if (ancestor[i][j - 1] != -1){
				ancestor[i][j] = ancestor[ancestor[i][j - 1]][j - 1];
			}
		}
	}
}

int lca(int u, int v){
	int i;

	if (depth[u] < depth[v]){
		swap(u, v);
	}

	for (i = L; i >= 0; i--){
		if (depth[u] - (1 << i) >= depth[v]){
			u = ancestor[u][i];
		}
	}

	if (u == v){
		return u;
	}

	for (i = L; i >= 0; i--){
		if (ancestor[u][i] != -1 and ancestor[u][i] != ancestor[v][i]){
			u = ancestor[u][i];
			v = ancestor[v][i];
		}
	}

	return parent[u];
}