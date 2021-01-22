class SparseTable {
  private:
    vector<vector<long long>> table;
    vector<long long> a;

    /* O(1) - Retrieves the index of the Most Significant Bit. */
    int msb_index(int mask) {
        return 8 * sizeof(mask) - __builtin_clz(mask) - 1;
    }

    /* O(1) - Retrieves ceil(log2(n)). */
    int floor_log2(int n) {
        assert(n > 0);
        return msb_index(n);
    }

    /* O(1) - Idempotent operation. f(f(x)) = f(x) or f(f(x, y), y) = f(x, f(x, y)) = f(x, y). */
    long long merge(long long x, long long y) {
        return max(x, y);
    }

  public:
    SparseTable() {}

    /* O(N * Log(N)). */
    SparseTable(vector<long long> const &a) {
        this->a = a;
        int k = floor_log2(a.size());

        // Allocating memory.
        table.resize(k + 1);

        for (int j = 0; j <= k; j++) {
            table[j].resize(a.size() - (1 << j) + 1);
        }

        // Base.
        for (int i = 0; i < a.size(); i++) {
            table[0][i] = a[i];
        }

        // Building for each 2^j <= n
        for (int j = 1; j <= k; j++) {
            // Building for each [i, i + 2^j - 1]
            for (int i = 0; i + (1 << j) - 1 < a.size(); i++) {
                table[j][i] = merge(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    /* O(1). */
    long long query(int l, int r) {
        // Finding greatest k such that 2^k <= r - l + 1
        int k = floor_log2(r - l + 1);
        return merge(table[k][l], table[k][r - ((1 << k) - 1)]);
    }
};
