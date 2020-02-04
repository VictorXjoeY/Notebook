#define LEFT(x) (x << 1)
#define RIGHT(x) ((x << 1) | 1)

/* O(1) - Retrieves the index of the Most Significant Bit. */
constexpr int msb_index(int mask) {
	return 8 * sizeof(mask) - __builtin_clz(mask) - 1;
}

/* O(1) - Retrieves ceil(log2(n)). */
constexpr int ceil_log2(int n) {
	assert(n > 0);
	return n == 1 ? 0 : msb_index(n - 1) + 1;
}

constexpr int N = 100000;
constexpr int L = ceil_log2(4 * N); // N rectangles but 4 * N y coordinates.
constexpr int OPEN = 0;
constexpr int CLOSE = 1;

struct Rectangle {
	long long xmin, ymin, xmax, ymax;
};

struct Event {
	long long x, ymin, ymax;
	int type;

	bool operator < (const Event &e) const {
		if (this->x == e.x) {
			return this->type < e.type;
		}

		return this->x < e.x;
	}
};

long long seg[1 << (L + 1)];
int active[1 << (L + 1)];
vector<long long> vy;

/* O(Log(N)). */
void update(int cur, int l, int r, long long i, long long j, int val) {
	int m = (l + r) / 2;

	if (vy[l] > j or vy[r] < i) {
		return;
	}

	if (vy[l] >= i and vy[r] <= j) {
		active[cur] += val;
		
		if (l == r) { // Leaf.
			seg[cur] = active[cur] > 0 ? vy[r + 1] - vy[l] : 0;
		}
		else {
			seg[cur] = active[cur] > 0 ? vy[r + 1] - vy[l] : seg[LEFT(cur)] + seg[RIGHT(cur)];
		}

		return;
	}

	update(LEFT(cur), l, m, i, j, val);
	update(RIGHT(cur), m + 1, r, i, j, val);

	// Merge.
	seg[cur] = active[cur] > 0 ? vy[r + 1] - vy[l] : seg[LEFT(cur)] + seg[RIGHT(cur)];
}

/* O(N * Log(N)) - Returns the area of the union of the rectangles. */
long long union_of_rectangles(const vector<Rectangle> &r) {
	long long last, ans;
	vector<Event> e;

	// No rectangles.
	if (r.empty()) {
		return 0;
	}

	// Initializing.
	vy.clear();

	// Rectangles are given as lattice points but events are about the grid 1x1 squares.
	for (int i = 0; i < r.size(); i++) {
		e.push_back({r[i].xmin, r[i].ymin, r[i].ymax - 1, OPEN});
		e.push_back({r[i].xmax - 1, r[i].ymin, r[i].ymax - 1, CLOSE});
		vy.push_back(r[i].ymin);
		vy.push_back(r[i].ymin + 1); // Sentinel.
		vy.push_back(r[i].ymax - 1);
		vy.push_back(r[i].ymax); // Sentinel.
	}

	// Sorting events and retrieving unique y coordinates.
	sort(e.begin(), e.end());
	sort(vy.begin(), vy.end());
	vy.resize(unique(vy.begin(), vy.end()) - vy.begin());

	// Initializing.
	last = e[0].x - 1;
	ans = 0;

	// Sweep line.
	for (int i = 0; i < e.size(); i++) {
		if (e[i].type == OPEN) {
			// Add until e[i].x - 1 to the answer.
			ans += ((e[i].x - 1) - last) * seg[1];
			update(1, 0, vy.size() - 1, e[i].ymin, e[i].ymax, 1);
			last = e[i].x - 1;
		}
		else if (e[i].type == CLOSE) {
			// Add until e[i].x to the answer.
			ans += (e[i].x - last) * seg[1];
			update(1, 0, vy.size() - 1, e[i].ymin, e[i].ymax, -1);
			last = e[i].x;
		}
	}

	return ans;
}