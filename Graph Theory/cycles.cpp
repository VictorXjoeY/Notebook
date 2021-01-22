constexpr int N = 100000;

vector<int> g[N + 1];     // (Input)
vector<int> cycle[N + 1]; // cycle[c] contains the vertices in the cycle c.
int color[N + 1];         // color[u] contains the index of the cycle that u belongs to. It is 0 for vertices that don't belong to a cycle.
bool in_stack[N + 1];
int parent[N + 1];
bool seen[N + 1];
int nc;
int n; // (Input)

/* O(V + E) - Finds all the cycles of an undirected graph that doesn't have any composite cycles. */
void dfs(int u) {
    in_stack[u] = seen[u] = true;

    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];

        if (!seen[v]) { // Not seen yet.
            parent[v] = u;
            dfs(v);
        } else if (v != parent[u] and in_stack[v]) { // Not current node's parent and is currently in stack. Found cycle.
            nc++;
            int p = u;

            // Backtracking through the entire cycle.
            while (p != v) {
                color[p] = nc;
                cycle[nc].push_back(p);
                p = parent[p];
            }

            color[v] = nc;
            cycle[nc].push_back(v);
        }
    }

    in_stack[u] = false;
}

/* O(V + E). */
void cycles() {
    // Clearing.
    memset(seen, false, sizeof(seen));
    memset(color, 0, sizeof(color));
    nc = 0;

    for (int u = 1; u <= n; u++) {
        cycle[u].clear();
    }

    // Running a DFS for every unseen vertex.
    for (int u = 1; u <= n; u++) {
        if (!seen[u]) {
            parent[u] = 0;
            dfs(u);
        }
    }
}