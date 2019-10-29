#define LEFT(x) (x << 1)
#define RIGHT(x) ((x << 1) | 1)

/* O(1) - Retrieves the index of the Most Significant Bit. */
constexpr int msb_index(int mask) {
	return 8 * sizeof(mask) - __builtin_clz(mask) - 1;
}

constexpr int N = 100000;
constexpr int L = msb_index(N - 1) + 1; // L = ceil(log(N))

struct Point{
	int x, y;
};

// The segment tree uses exactly 2 * N - 1 nodes, but we need at least 2^(ceil(log(N)) + 1) - 1 when we index the tree using
// 2 * cur and 2 * cur + 1. This value can be further simplified by a more relaxed upperbound of  4 * N - 5 nodes.
vector<Point> p; // (Input) Points.
vector<int> vx; // X coordinates (sorted and unique).
vector<int> seg_x[1 << (L + 1)]; // Segments of y coordinates (sorted and unique).
vector<int> seg_y[1 << (L + 1)]; // Segment Trees on y.
vector<vector<int>> mx; // Unique y values for every x value.
vector<int> dp;

/* O(1) - Merge for seg_y[][]. */
int merge_y(int nl, int nr) {
	return max(nl, nr);
}

/* O(N) - Merge for seg_x[]. */
vector<int> merge_x(const vector<int> &nl, const vector<int> &nr) {
	vector<int> ans;

	ans.resize(nl.size() + nr.size());
	merge(nl.begin(), nl.end(), nr.begin(), nr.end(), ans.begin());
	ans.resize(unique(ans.begin(), ans.end()) - ans.begin());

	return ans;
}

/* O(N) - Builds a segment tree over a 0-based array of y values. Called as build_y(1, 0, seg_x[cur].size() - 1) by build_x(). */
void build_y(vector<int> &seg, const vector<int> &vy, int cur, int l, int r) {
	int m = (l + r) / 2;

	if (l == r) {
		// This node should represent the point vy[l].
		seg[cur] = 0;
		return;
	}

	// Building children.
	build_y(seg, vy, LEFT(cur), l, m);
	build_y(seg, vy, RIGHT(cur), m + 1, r);

	// Merging.
	seg[cur] = merge_y(seg[LEFT(cur)], seg[RIGHT(cur)]);
}

/* O(N) - Builds a segment tree over a 0-based array of points. Use build_x(1, 0, vx.size() - 1) to build. */
void build_x(int cur, int l, int r) {
	int i, m = (l + r) / 2;

	if (l == r) { // Creating leaf and building segment tree on y coordinate.
		// Inserting every unique sorted y coordinate that has vx[l] as x coordinate.
		for (i = 0; i < mx[l].size(); i++) {
			seg_x[cur].push_back(mx[l][i]);
		}

		// Allocating memory for the segment tree stored in this leaf.
		seg_y[cur].resize(1 << (msb_index(seg_x[cur].size() - 1) + 2));
		build_y(seg_y[cur], seg_x[cur], 1, 0, seg_x[cur].size() - 1);
		return;
	}

	// Building children.
	build_x(LEFT(cur), l, m);
	build_x(RIGHT(cur), m + 1, r);

	// Merging and building segment tree on y coordinates.
	seg_x[cur] = merge_x(seg_x[LEFT(cur)], seg_x[RIGHT(cur)]);
	seg_y[cur].resize(1 << (msb_index(seg_x[cur].size() - 1) + 2));
	build_y(seg_y[cur], seg_x[cur], 1, 0, seg_x[cur].size() - 1);
}

/* O(Log(N)) - Query called by query_x(). */
int query_y(vector<int> &seg, const vector<int> &vy, int cur, int l, int r, int yi, int yf) {
	int nl, nr, m = (l + r) / 2;

	if (vy[l] > yf or vy[r] < yi) {
		return 0;
	}

	if (vy[l] >= yi and vy[r] <= yf) {
		return seg[cur];
	}

	nl = query_y(seg, vy, LEFT(cur), l, m, yi, yf);
	nr = query_y(seg, vy, RIGHT(cur), m + 1, r, yi, yf);

	return merge_y(nl, nr);
}

/* O(Log^2(N)) - Query. query_x(1, 0, vx.size() - 1, xi, xf, yi, yf) */
int query_x(int cur, int l, int r, int xi, int xf, int yi, int yf) {
	int nl, nr, m = (l + r) / 2;

	if (vx[l] > xf or vx[r] < xi) {
		return 0;
	}

	if (vx[l] >= xi and vx[r] <= xf) {
		return query_y(seg_y[cur], seg_x[cur], 1, 0, seg_x[cur].size() - 1, yi, yf);
	}

	nl = query_x(LEFT(cur), l, m, xi, xf, yi, yf);
	nr = query_x(RIGHT(cur), m + 1, r, xi, xf, yi, yf);

	return merge_y(nl, nr);
}

/* O(Log(N)) - Update called by update_x(). */
void update_y(vector<int> &seg, const vector<int> &vy, int cur, int l, int r, int y, int val) {
	int m = (l + r) / 2;

	// Outside of the update range.
	if (vy[l] > y or vy[r] < y) {
		return;
	}

	// Found node with the correct y value. Not necessarily a leaf node.
	if (vy[l] == vy[r]) {
		seg[cur] = max(seg[cur], val);
		return;
	}

	// Updating children.
	update_y(seg, vy, LEFT(cur), l, m, y, val);
	update_y(seg, vy, RIGHT(cur), m + 1, r, y, val);

	// Merging.
	seg[cur] = merge_y(seg[LEFT(cur)], seg[RIGHT(cur)]);
}

/* O(Log^2(N)) - Update. update_x(1, 0, vx.size() - 1, x, y, val) */
void update_x(int cur, int l, int r, int x, int y, int val) {
	int nl, nr, m = (l + r) / 2;

	// Outside of update range.
	if (vx[l] > x or vx[r] < x) {
		return;
	}
	
	// Found node with the correct x value. Not necessarily a leaf node.
	if (vx[l] == vx[r]) {
		update_y(seg_y[cur], seg_x[cur], 1, 0, seg_x[cur].size() - 1, y, val);
		return;
	}

	// Updating children.
	update_x(LEFT(cur), l, m, x, y, val);
	update_x(RIGHT(cur), m + 1, r, x, y, val);

	// Querying for the new best value of coordinate y for this range of x represented by [l, r].
	nl = query_y(seg_y[LEFT(cur)], seg_x[LEFT(cur)], 1, 0, seg_x[LEFT(cur)].size() - 1, y, y);
	nr = query_y(seg_y[RIGHT(cur)], seg_x[RIGHT(cur)], 1, 0, seg_x[RIGHT(cur)].size() - 1, y, y);

	// Merging by updating the new best value.
	update_y(seg_y[cur], seg_x[cur], 1, 0, seg_x[cur].size() - 1, y, merge_y(nl, nr));
}

/* O(N * Log(N)) */
void init() {
	int pos;

	// Retrieving x coordinates.
	for (int i = 0; i < p.size(); i++) {
		vx.push_back(p[i].x);
	}

	// Making x coordinates unique.
	sort(vx.begin(), vx.end());
	vx.resize(unique(vx.begin(), vx.end()) - vx.begin());

	// Retrieving y coordinates for every x coordinate.
	mx.resize(vx.size());

	for (int i = 0; i < p.size(); i++) {
		pos = lower_bound(vx.begin(), vx.end(), p[i].x) - vx.begin();
		mx[pos].push_back(p[i].y);
	}

	// Making y coordinates unique for every x coordinate.
	for (int i = 0; i < mx.size(); i++) {
		sort(mx[i].begin(), mx[i].end());
		mx[i].resize(unique(mx[i].begin(), mx[i].end()) - mx[i].begin());
	}

	// Building.
	build_x(1, 0, vx.size() - 1);
}

/* O(N * Log^2(N)). */
int lis_2d() {
	init();
	dp.resize(p.size());

	// Filling dp.
	for (int i = 0; i < p.size(); i++) {
		dp[i] = 1 + query_x(1, 0, vx.size() - 1, 1, p[i].x, 1, p[i].y);
		update_x(1, 0, vx.size() - 1, p[i].x, p[i].y, dp[i]);
	}

	// Returning LIS.
	return *max_element(dp.begin(), dp.end());
}