#define N 100000

vector<int> cycle[N + 1]; // cycle[c] contains the vertices in the cycle c.
int color[N + 1]; // color[u] contains the index of the cycle that u belongs to.
vector<int> g[N + 1]; // (Input)
bool in_stack[N + 1];
int parent[N + 1];
bool seen[N + 1];
int cycle_count;
int n; // (Input)

/* O(V + E) - Finds all the cycles of a graph that doesn't have any composite cycles. */
void dfs(int u){
	int p, v, i;

	in_stack[u] = true;
	seen[u] = true;

	for (i = 0; i < (int)g[u].size(); i++){
		v = g[u][i];

		if (!seen[v]){ // Not seen yet.
			parent[v] = u;
			dfs(v);
		}
		else if (v != parent[u] and in_stack[v]){ // Not current node's parent and is currently in stack. Found cycle.
			cycle_count++;
			p = u;

			// Backtracking through the entire cycle.
			while (p != v){
				color[p] = cycle_count;
				cycle[cycle_count].push_back(p);
				p = parent[p];
			}

			color[v] = cycle_count;
			cycle[cycle_count].push_back(v);
		}
	}

	in_stack[u] = false;
}

void cycles(){
	int u;

	for (u = 1; u <= n; u++){
		if (!seen[u]){
			dfs(u);
		}
	}
}