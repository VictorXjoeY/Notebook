constexpr int INF = 0x3f3f3f3f;
constexpr int N = 100;

bool seen[N + 1];
int C[N + 1][N + 1]; // (Input)
int T[N + 1][N + 1];
int F[N + 1][N + 1];
int P[N + 1];
int M[N + 1];
int n; // (Input)

/* O(V + E). */
int bfs(int s, int t){
	queue<int> q;

	memset(M, 0, sizeof(M));
	memset(P, -1, sizeof(P));
	M[s] = INF;
	P[s] = -2;

	q.push(s);

	while (!q.empty()){
		int u = q.front();
		q.pop();

		for (int v = 1; v <= n; v++){
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

/* O(V * E^2). */
int edmonds_karp(int s, int t){
	int f, m;

	// Copying the capacities.
	for (int u = 1; u <= n; u++){
		for (int v = 1; v <= n; v++){
			T[u][v] = C[u][v];
		}
	}

	// Initializing the flow with 0.
	memset(F, 0, sizeof(F));
	f = 0;

	// While I can improve the flow.
	while (true){
		// Finding an augmenting path.
		m = bfs(s, t);

		// Cannot improve the flow.
		if (!m){
			break;
		}

		f += m;
		int v = t;

		// Updating the flow throughout the path found by BFS.
		while (v != s){
			int u = P[v];

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
	seen[u] = true;

	for (int v = 1; v <= n; v++){
		if (T[u][v] and !seen[v]){
			dfs(v);
		}
	}
}

void min_cut(int s, int t){
	edmonds_karp(s, t);
	dfs(s);

	for (int u = 1; u <= n; u++){
		for (int v = 1; v <= n; v++){
			if (seen[u] and !seen[v] and C[u][v]){
				printf("%d %d\n", u, v);
			}
		}
	}
}