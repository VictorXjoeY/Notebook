#define N 100000

vector<int> g[N + 1];
bool seen[N + 1];
int d[N + 1];
int f[N + 1];
int p[N + 1];
int timer;

void dfs(int u){
	int v, i;

	seen[u] = true;
	d[u] = timer;
	timer++;

	for (i = 0; i < (int)g[u].size(); i++){
		v = g[u][i];

		if (!seen[v]){
			p[v] = u;
			dfs(v);
		}
	}

	f[u] = timer;
	timer++;
}