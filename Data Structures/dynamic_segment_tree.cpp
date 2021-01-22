/* O(1) - Retrieves the index of the Most Significant Bit. */
constexpr int msb_index(int mask) {
    return 8 * sizeof(mask) - __builtin_clz(mask) - 1;
}

/* O(1) - Retrieves ceil(log2(n)). */
constexpr int floor_log2(int n) {
    assert(n > 0);
    return msb_index(n);
}

constexpr int MIN = 1;
constexpr int MAX = 1000000000;
constexpr int RANGE = MAX - MIN + 1; // RANGE >= 4 * Q
constexpr int Q = 100000;            // Number of range updates.
constexpr int L = floor_log2(RANGE);
constexpr int LQ = floor_log2(Q);

// Every node in this tree other than the leaves has 2 children. Leaves have seg[cur] = 0 but will have a lazy[cur] != 0 after updates.
// We assume that RANGE >= 4 * Q, you wouldn't need to use the dynamic segment tree otherwise.
// This tree uses exactly 2^(floor(log(Q)) + 3) - 1 + 4 * (floor(log(RANGE)) - floor(log(Q)) - 2) * Q + min(2 * (RANGE - 2^floor(log(RANGE)), 4 * Q).
// This value can be further simplified by a more relaxed upperbound of 4 * (floor(log(RANGE)) - floor(log(Q)) + 1) * Q - 1 nodes.
long long seg[(1 << (LQ + 3)) + 4 * (L - LQ - 2) * Q + min(2 * (RANGE - (1 << L)), 4 * Q)]; // seg[0] should store the neutral value for the merge operation.
long long lazy[(1 << (LQ + 3)) + 4 * (L - LQ - 2) * Q + min(2 * (RANGE - (1 << L)), 4 * Q)];
int lchild[(1 << (LQ + 3)) + 4 * (L - LQ - 2) * Q + min(2 * (RANGE - (1 << L)), 4 * Q)];
int rchild[(1 << (LQ + 3)) + 4 * (L - LQ - 2) * Q + min(2 * (RANGE - (1 << L)), 4 * Q)];
int root, last;

/* O(1) - Returns the real value of the node, considering its lazy value. */
long long value(int cur, int l, int r) {
    return seg[cur] + (r - l + 1) * lazy[cur];
}

/* O(1) - Updates the current node with lazy and flushes down the lazyness. */
void lazy_update(int cur, int l, int r) {
    seg[cur] = value(cur, l, r);

    if (l < r) {            // Not a length 1 range.
        if (!lchild[cur]) { // Creating left child.
            lchild[cur] = ++last;
        }

        if (!rchild[cur]) { // Creating right child.
            rchild[cur] = ++last;
        }

        // Marking children as lazy.
        lazy[lchild[cur]] += lazy[cur];
        lazy[rchild[cur]] += lazy[cur];
    }

    // Marking current node as not lazy.
    lazy[cur] = 0;
}

/* O(1) - Merges the children's values. */
long long merge(long long nl, long long nr) {
    return nl + nr;
}

/* O(Log(MAX)) - Call root = update(root, MIN, MAX, i, j, x) */
int update(int cur, int l, int r, int i, int j, long long x) {
    int m = (l + r) / 2;

    if (l > j or r < i) { // Out of range.
        return cur;
    }

    if (!cur) { // Creating the current range.
        cur = ++last;
    }

    if (l >= i and r <= j) { // Fully in range.
        lazy[cur] += x;
        return cur;
    }

    // Only flush down the lazyness if we're going to call for children nodes.
    if (lazy[cur]) {
        lazy_update(cur, l, r);
    }

    // Updating children and linking the tree.
    lchild[cur] = update(lchild[cur], l, m, i, j, x);
    rchild[cur] = update(rchild[cur], m + 1, r, i, j, x);

    // Merging children's results.
    seg[cur] = merge(value(lchild[cur], l, m), value(rchild[cur], m + 1, r));

    return cur;
}

/* O(Log(MAX)) - Call ans = query(root, MIN, MAX, i, j) */
long long query(int cur, int l, int r, int i, int j) {
    int m = (l + r) / 2;
    long long nl, nr;

    if (l > j or r < i) { // Out of range.
        return 0;
    }

    if ((l >= i and r <= j) or (!lchild[cur] and !rchild[cur])) { // Fully in range or leaf.
        return value(cur, max(l, i), min(r, j));
    }

    // Only flush down the lazyness if we're going to call for children nodes.
    if (lazy[cur]) {
        lazy_update(cur, l, r);
    }

    // Has both children, querying downwards.
    nl = query(lchild[cur], l, m, i, j);
    nr = query(rchild[cur], m + 1, r, i, j);

    return merge(nl, nr);
}
