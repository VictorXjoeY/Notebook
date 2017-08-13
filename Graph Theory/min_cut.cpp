#define INF 0x3f3f3f3f
#define N 100

bool seen[N + 1];
int C[N + 1][N + 1];
int T[N + 1][N + 1];
int F[N + 1][N + 1];
int P[N + 1];
int M[N + 1];
int n;

int bfs(int s, int t){
	queue<int> q;
	int u, v;

	memset(M, 0, sizeof(M));
	memset(P, -1, sizeof(P));
	M[s] = INF;
	P[s] = -2;

	q.push(s);

	while (!q.empty()){
		u = q.front();
		q.pop();

		for (v = 1; v <= n; v++){
			if (v != u and T[u][v] > 0 and P[v] == -1){
				P[v] = u;
				M[v] = min(M[u], C[u][v] - F[u][v]);

				if (v != t){
					q.push(v);
				}
				else{
					return M[t];
				}
			}
		}
	}

	return 0;
}

int edmonds_karp(int s, int t){
	int f, m, u, v;

	for (u = 1; u <= n; u++){
		for (v = 1; v <= n; v++){
			T[u][v] = C[u][v];
		}
	}

	memset(F, 0, sizeof(F));
	f = 0;

	while (true){
		m = bfs(s, t);

		if (!m){
			break;
		}

		f += m;
		v = t;

		while (v != s){
			u = P[v];

			F[u][v] += m;
            F[v][u] -= m;
            T[u][v] -= m;
            T[v][u] += m;

            v = u;
		}
	}

	return f;
}

void dfs(int u){
	int v;

	seen[u] = true;

	for (v = 1; v <= n; v++){
		if (T[u][v] and !seen[v]){
			dfs(v);
		}
	}
}

void min_cut(int s, int t){
	int u, v;

	edmonds_karp(s, t);
	dfs(s);

	for (u = 1; u <= n; u++){
		for (v = 1; v <= n; v++){
			if (seen[u] and !seen[v] and C[u][v]){
				printf("%d %d\n", u, v);
			}
		}
	}
}