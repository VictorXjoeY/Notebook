#define N 100000
#define LEFT(x) (x << 1)
#define RIGHT(x) ((x << 1) | 1)

struct Point{
	int x, y;

	bool operator < (const Point &b) const{
		if (this->x == b.x){
			return this->y < b.y;
		}

		return this->x < b.x;
	}
};

Point p[N + 1]; // Points.
Point px[N + 1]; // Points sorted by x.
vector<int> seg_x[4 * N + 1]; // Segments sorted by y.
vector<int> seg_y[4 * N + 1]; // Segment Trees on y.
int dp[N + 1];
int n;

/* O(1) - Merge for seg_y[][]. */
int merge_y(int nl, int nr){
	return max(nl, nr);
}

/* O(N) - Merge for seg_x[]. */
vector<int> merge_x(const vector<int> &nl, const vector<int> &nr){
	vector<int> ans;

	ans.resize(nl.size() + nr.size());
	merge(nl.begin(), nl.end(), nr.begin(), nr.end(), ans.begin());

	return ans;
}

/* O(N) - Builds a segment tree over a 0-based array of y values. Called as build_y(1, 0, seg_x[cur].size() - 1) by build_x(). */
void build_y(vector<int> &seg, const vector<int> &vy, int cur, int l, int r){
	int m = (l + r) / 2;

	if (l == r){
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

/* O(N * Log(N)) - Builds a segment tree over a 0-based array of points. Use build_x(1, 0, n - 1) to build. */
void build_x(int cur, int l, int r){
	int m = (l + r) / 2;

	// Allocating memory for the segment tree stored in this node.
	seg_y[cur].resize(4 * (r - l + 1) + 1);
	
	if (l == r){
		// Creating leaf and building segment tree on y coordinate.
		seg_x[cur].push_back(px[l].y);
		build_y(seg_y[cur], seg_x[cur], 1, 0, seg_x[cur].size() - 1);
		return;
	}

	// Building children.
	build_x(LEFT(cur), l, m);
	build_x(RIGHT(cur), m + 1, r);

	// Merging and building segment tree on y coordinates.
	seg_x[cur] = merge_x(seg_x[LEFT(cur)], seg_x[RIGHT(cur)]);
	build_y(seg_y[cur], seg_x[cur], 1, 0, seg_x[cur].size() - 1);
}

/* O(Log(N)) - Query called by query_x(). */
int query_y(vector<int> &seg, const vector<int> &vy, int cur, int l, int r, int yi, int yf){
	int nl, nr, m = (l + r) / 2;

	if (vy[l] > yf or vy[r] < yi){
		return 0;
	}

	if (vy[l] >= yi and vy[r] <= yf){
		return seg[cur];
	}

	nl = query_y(seg, vy, LEFT(cur), l, m, yi, yf);
	nr = query_y(seg, vy, RIGHT(cur), m + 1, r, yi, yf);

	return merge_y(nl, nr);
}

/* O(Log^2(N)) - Query. */
int query_x(int cur, int l, int r, int xi, int xf, int yi, int yf){
	int nl, nr, m = (l + r) / 2;

	if (px[l].x > xf or px[r].x < xi){
		return 0;
	}

	if (px[l].x >= xi and px[r].x <= xf){
		return query_y(seg_y[cur], seg_x[cur], 1, 0, seg_x[cur].size() - 1, yi, yf);
	}

	nl = query_x(LEFT(cur), l, m, xi, xf, yi, yf);
	nr = query_x(RIGHT(cur), m + 1, r, xi, xf, yi, yf);

	return merge_y(nl, nr);
}

/* O(Log(N)) - Update called by update_x(). */
void update_y(vector<int> &seg, const vector<int> &vy, int cur, int l, int r, int y, int val){
	int m = (l + r) / 2;

	// Outside of the update range.
	if (vy[l] > y or vy[r] < y){
		return;
	}

	// Found node with the correct y value. Not necessarily a leaf node.
	if (vy[l] == vy[r]){
		seg[cur] = max(seg[cur], val);
		return;
	}

	// Updating children.
	update_y(seg, vy, LEFT(cur), l, m, y, val);
	update_y(seg, vy, RIGHT(cur), m + 1, r, y, val);

	// Merging.
	seg[cur] = merge_y(seg[LEFT(cur)], seg[RIGHT(cur)]);
}

/* O(Log^2(N)) - Update. */
void update_x(int cur, int l, int r, int x, int y, int val){
	int nl, nr, m = (l + r) / 2;

	// Outside of update range.
	if (px[l].x > x or px[r].x < x){
		return;
	}
	
	// Found node with the correct x value. Not necessarily a leaf node.
	if (px[l].x == px[r].x){
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

/* O(N * Log^2(N)). */
int lis_2d(){
	int i;

	// Copying points into px.
	for (i = 0; i < n; i++){
		px[i] = p[i];
	}

	// Sorting by x.
	sort(px, px + n);

	// Building.
	build_x(1, 0, n - 1);

	// Filling dp.
	for (i = 0; i < n; i++){
		dp[i] = 1 + query_x(1, 0, n - 1, 1, p[i].x, 1, p[i].y);
		update_x(1, 0, n - 1, p[i].x, p[i].y, dp[i]);
	}

	// Returning LIS.
	return *max_element(dp, dp + n);
}