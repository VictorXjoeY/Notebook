class UnionFind {
  private:
    vector<int> p, size;
    int n;

  public:
    UnionFind() {}

    UnionFind(int n) {
        // Initializing.
        size.assign(n + 1, 1);
        p.resize(n + 1);
        this->n = n;

        // Setting the representative of each set to be itself.
        for (int i = 1; i <= n; i++) {
            p[i] = i;
        }
    }

    /* Amortized O(1). */
    int find_set(int u) {
        if (u == p[u]) { // Found representative.
            return u;
        }

        // Compressing the path as we search for the set's representative.
        return p[u] = find_set(p[u]);
    }

    /* Amortized O(1). */
    void union_set(int u, int v) {
        // Finding representatives of u and v.
        int x = find_set(u);
        int y = find_set(v);

        // If u and v belong to different sets.
        if (x != y) {
            // Attaching the smaller tree to the bigger tree.
            if (size[x] < size[y]) {
                p[x] = y;
                size[y] += size[x];
            } else {
                p[y] = x;
                size[x] += size[y];
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