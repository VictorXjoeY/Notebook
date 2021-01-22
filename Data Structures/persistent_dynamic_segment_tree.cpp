/* O(1) - Retrieves the index of the Most Significant Bit. */
constexpr int msb_index(int mask) {
    return 8 * sizeof(mask) - __builtin_clz(mask) - 1;
}

/* O(1) - Retrieves ceil(log2(n)). */
constexpr int ceil_log2(int n) {
    assert(n > 0);
    return n == 1 ? 0 : msb_index(n - 1) + 1;
}

constexpr int MIN = 1;
constexpr int MAX = 1000000000;
constexpr int RANGE = MAX - MIN + 1;
constexpr int T = 100000;           // Number of range updates.
constexpr int L = ceil_log2(RANGE); // L = ceil(log(RANGE))

// Every node in this tree other than the leaves have 2 children. Only leaves are lazy.
// The dynamic segment tree uses exactly (4 * ceil(log(RANGE)) - 1) * T nodes in the worst case, in which each update will add 4 * ceil(log(RANGE)) - 1 nodes.
long long seg[(4 * L - 1) * T + 1];  // seg[0] should store the neutral value for the merge operation.
long long lazy[(4 * L - 1) * T + 1]; // lazy[0] should store the neutral value for the lazyness.
int lchild[(4 * L - 1) * T + 1];
int rchild[(4 * L - 1) * T + 1];
int root[T + 1];
int last;

/* O(1) - Returns the real value of the node, considering its lazy value. */
long long value(int cur, int l, int r) {
    return seg[cur] + (r - l + 1) * lazy[cur];
}

/* O(1) - Merges the children's values. */
long long merge(long long nl, long long nr) {
    return nl + nr;
}

/* O(Log(MAX)) - Use root[t] = update(root[t - 1], MIN, MAX, 0, i, j, x) */
int update(int cur, int l, int r, long long prop, int i, int j, long long x) {
    int ncur, m = (l + r) / 2;

    if (l > j or r < i) { // Out of range.
        return cur;
    }

    ncur = ++last; // New node.
    lchild[ncur] = lchild[cur];
    rchild[ncur] = rchild[cur];

    if (l >= i and r <= j) { // Fully in range. "Leaf" of current update.
        lazy[ncur] = prop + x;
    } else { // Partially in range.
        // Updating children and linking the tree. Propagate downwards a value only if cur is a leaf.
        lchild[ncur] = update(lchild[cur], l, m, prop + lazy[cur], i, j, x);
        rchild[ncur] = update(rchild[cur], m + 1, r, prop + lazy[cur], i, j, x);
    }

    // Merging children's results, even if the current node was fully in range.
    seg[ncur] = merge(value(lchild[ncur], l, m), value(rchild[ncur], m + 1, r));

    return ncur;
}

/* O(Log(MAX)) - Use query(root[k], MIN, MAX, 0, i, j) to query after the k'th update */
long long query(int cur, int l, int r, long long prop, int i, int j) {
    int m = (l + r) / 2;
    long long nl, nr;

    if (l > j or r < i) { // Out of range.
        return 0;
    }

    if ((l >= i and r <= j) or (!lchild[cur] and !rchild[cur])) { // Fully in range or leaf.
        return value(cur, max(l, i), min(r, j)) + (min(r, j) - max(l, i) + 1) * prop;
    }

    // Has both children, querying downwards.
    nl = query(lchild[cur], prop + lazy[cur], l, m, i, j);
    nr = query(rchild[cur], prop + lazy[cur], m + 1, r, i, j);

    return merge(nl, nr);
}
