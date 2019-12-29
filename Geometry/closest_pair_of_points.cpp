constexpr double INF = 1e18;

struct Point {
	double x, y;
	int idx; 
};

/* O(1). */
bool comp_x(const Point &a, const Point &b) {
	return a.x < b.x;
}

/* O(1). */
bool comp_y(const Point &a, const Point &b) {
	return a.y < b.y;
}

/* O(1). */
double dist(const Point &a, const Point &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

/* O(10 * N * Log(N)) - Recursively finds the closest pair of points and their distance. */
tuple<int, int, double> closest_pair_of_points(int l, int r, const vector<Point> &px, vector<Point> &py) {
	int al, bl, ar, br, a, b, m = (l + r) / 2;
	vector<Point> pyl, pyr, strip;
	double dl, dr, d;

	// Base case.
	if (l == r) {
		py = {px[l]};
		return {px[l].idx, px[l].idx, INF};
	}

	// Solving recursively.
	tie(al, bl, dl) = closest_pair_of_points(l, m, px, pyl);
	tie(ar, br, dr) = closest_pair_of_points(m + 1, r, px, pyr);

	// Merging the points sorted by y.
	py.resize(pyl.size() + pyr.size());
	merge(pyl.begin(), pyl.end(), pyr.begin(), pyr.end(), py.begin(), comp_y);

	// Initializing closest pair of points for the current range.
	if (dl < dr) {
		tie(d, a, b) = {dl, al, bl};
	}
	else {
		tie(d, a, b) = {dr, ar, br};
	}

	// Retrieving the strip of relevant points.
	for (int i = 0; i < py.size(); i++) {
		if (abs(py[i].x - px[m].x) <= d) {
			strip.push_back(py[i]);
		}
	}

	// O(10 * N) - Closest left-right pair of points. 
	for (int i = 0; i < strip.size(); i++) {
		// Checking 5 points below and 5 points above.
		for (int j = max(0, i - 5); j < min((int)strip.size(), i + 6); j++) {
			if (i != j and dist(strip[i], strip[j]) < d) {
				d = dist(strip[i], strip[j]);
				a = strip[i].idx;
				b = strip[j].idx;
			}
		}
	}

	return {a, b, d};
}

/* O(10 * N * Log(N)) - Returns (a, b, d) such that a and b are the indices of the closest points and d is their distance. */
tuple<int, int, double> closest_pair_of_points(const vector<Point> &p) {
	vector<Point> px, py;

	px = p;
	sort(px.begin(), px.end(), comp_x);

	return closest_pair_of_points(0, p.size() - 1, px, py);
}