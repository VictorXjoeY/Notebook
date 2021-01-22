constexpr int N = 100000;
constexpr int Q = 100000;

class UnionFind {
  private:
    vector<int> p, rank, size;
    int n;

  public:
    UnionFind() {}

    UnionFind(int n) {
        // Initializing.
        size.assign(n, 1); // Size of sets is 1 initially.
        rank.assign(n, 0); // Rank of sets is 0 initially.
        p.resize(n);
        this->n = n;

        // Setting the representative to be itself for each set.
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
    }

    /* O(1). */
    int find_set(int u) {
        // Found representative.
        if (u == p[u]) {
            return u;
        }

        // Compressing the path as we search for the set's representative.
        return p[u] = find_set(p[u]);
    }

    /* O(1). */
    void union_set(int u, int v) {
        // Finding representatives of u and v.
        int x = find_set(u);
        int y = find_set(v);

        // If u and v belong to different sets.
        if (x != y) {
            if (rank[x] > rank[y]) { // Attaching y's tree to the root x.
                size[x] += size[y];
                p[y] = x;
            } else if (rank[x] < rank[y]) { // Attaching x's tree to the root y.
                size[y] += size[x];
                p[x] = y;
            } else { // Can attach either one. Attaching y's tree to the root x. Rank increases by one.
                size[x] += size[y];
                p[y] = x;
                rank[x]++;
            }

            // Decreasing number of sets.
            n--;
        }
    }

    /* O(1). */
    int num_sets() {
        return n;
    }

    /* O(1). */
    int set_size(int u) {
        return size[find_set(u)];
    }
};

vector<int> g[N + 1];             // (Input)
vector<pair<int, int>> gq[N + 1]; // gq[u].first = v and gq[u].second = query index
pair<int, int> queries[Q + 1];    // (Input) Each pair is a query for the lca(u, v)
int ancestor[N + 1];
bool seen[N + 1];
int ans[Q + 1]; // (Output)
int n, q;       // (Input)
UnionFind uf;

/* O(V). */
void dfs(int u) {
    seen[u] = true;
    ancestor[u] = u;

    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];

        if (!seen[v]) {
            dfs(v);
            uf.union_set(u, v); // Merging v's subtree in u's set.

            // This is necessary because we need the set that contains u to have u as the ancestor
            // and union_set(u, v) might have changed the representative of the set.
            ancestor[uf.find_set(u)] = u;
        }
    }

    for (int i = 0; i < gq[u].size(); i++) {
        int v = gq[u][i].first;
        int idx = gq[u][i].second;

        if (seen[v]) {
            // v is currently in the set in which its "representative" (ancestor[representative]) is the lca(u, v).
            ans[idx] = ancestor[uf.find_set(v)];
        }
    }
}

/* O(V + Q). */
void lca(int root) {
    // Clearing.
    memset(seen, false, sizeof(seen));
    uf = UnionFind(n + 1);

    for (int u = 1; u <= n; u++) {
        gq[u].clear();
    }

    // O(Q) - Builds the queries adjacency list.
    for (int i = 1; i <= q; i++) {
        int u = queries[i].first;
        int v = queries[i].second;
        gq[u].push_back({v, i});
        gq[v].push_back({u, i});
    }

    // Depth-first search to answer queries.
    dfs(root);
}