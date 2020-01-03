struct Point {
	long long x, y;

	/* O(1) - Vector subtraction. */
	Point operator - (const Point &b) const {
		return {this->x - b.x, this->y - b.y};
	}

	/* O(1) - Dot product. */
	long long operator * (const Point &b) const {
		return this->x * b.x + this->y * b.y;
	}

	/* O(1) - Cross product. */
	long long operator ^ (const Point &b) const {
		return this->x * b.y - this->y * b.x;
	}
};

/* O(N) - Computes twice the signed area of a convex or non-convex polygon, being it simple or self-intersecting.
   Expects a polygon either in clockwise or in counter-clockwise order. */
long long shoelace(const vector<Point> &p) {
	long long ans = 0;

	for (int i = 0; i < p.size(); i++) {
		ans += p[i] ^ p[(i + 1) % p.size()];
	}

	return ans;
}

/* O(N) - Returns true if the points of the given simple polygon are in clockwise order. */ 
bool is_clockwise(const vector<Point> &p) {
	return shoelace(p) < 0;
}

/* O(1) - Returns true if point Q is inside triangle ABC or on one of its edges. */ 
bool point_inside_triangle(const Point &q, const Point &a, const Point &b, const Point &c) {
	return (((b - a) ^ (q - a)) >= 0 and ((c - b) ^ (q - b)) >= 0 and ((a - c) ^ (q - c)) >= 0) or (((b - a) ^ (q - a)) <= 0 and ((c - b) ^ (q - b)) <= 0 and ((a - c) ^ (q - c)) <= 0);
}

/* O(1) - Returns true if p[i] is a convex vertex. */
bool is_convex(const vector<Point> &p, const vector<int> &l, const vector<int> &r, int i) {
	return ((p[i] - p[l[i]]) ^ (p[r[i]] - p[l[i]])) > 0;
}

/* O(1) - Returns true if p[b] is an ear. */
bool is_ear(const vector<Point> &p, const vector<int> &l, const vector<int> &r, int i) {
	// Ear has to be convex.
	if (!is_convex(p, l, r, i)) {
		return false;
	}

	// For each point currently in the polygon, except for l[i], i and r[i].
	for (int j = r[r[i]]; j != l[i]; j = r[j]) {
		// If there's a point inside the triangle (p[l[i]], p[i], p[r[i]]) then p[i] is not an ear.
		if (point_inside_triangle(p[j], p[l[i]], p[i], p[r[i]])) {
			return false;
		}
	}

	return true;
}

/* O(N^2) - Returns a triangulation of the given simple polygon. */
vector<vector<Point>> triangulation(vector<Point> p) {
	vector<vector<Point>> ans;
	vector<bool> clipped;
	vector<int> l, r;
	queue<int> q;

	// Making it counter-clockwise.
	if (is_clockwise(p)) {
		reverse(p.begin(), p.end());
	}

	// Initializing.
	int n = p.size();
	clipped.assign(n, false);
	l.resize(n);
	r.resize(n);

	for (int i = 0; i < n; i++) {
		l[i] = (i - 1 + n) % n;
		r[i] = (i + 1) % n;
		q.push(i);
	}

	// While the remaining polygon is not a triangle.
	while (n >= 3) {
		// Retrieving possible ear.
		int i = q.front();
		q.pop();

		// If it is an ear.
		if (!clipped[i] and is_ear(p, l, r, i)) {
			// Pushing triangle into the answer.
			ans.push_back({p[l[i]], p[i], p[r[i]]});

			// Clipping ear.
			clipped[i] = true;
			r[l[i]] = r[i];
			l[r[i]] = l[i];

			// Pushing adjacent.
			q.push(l[i]);
			q.push(r[i]);

			// Updating number of remaining vertices.
			n--;
		}
	}

	return ans;
}
