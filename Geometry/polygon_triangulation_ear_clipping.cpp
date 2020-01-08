template <class T>
struct Point {
	T x, y;

	/* O(1) - Vector subtraction. */
	Point<T> operator - (const Point<T> &b) const {
		return {this->x - b.x, this->y - b.y};
	}

	/* O(1) - Dot product. */
	T operator * (const Point<T> &b) const {
		return (this->x * b.x) + (this->y * b.y);
	}

	/* O(1) - Cross product. */
	T operator ^ (const Point<T> &b) const {
		return (this->x * b.y) - (this->y * b.x);
	}

	/* O(1) - Equal. */
	bool operator == (const Point &b) const {
		return this->x == b.x and this->y == b.y;
	}
};

/* O(1) - Returns true if the point Q is inside the line defined by AB.
   Expects a non-degenerate line AB. */
template <class T>
bool point_inside_line(const Point<T> &q, const Point<T> &a, const Point<T> &b) {
	return ((b - a) ^ (q - a)) == static_cast<T>(0);
}

/* O(1) - Returns -1 if Q is inside the segment AB, 0 if on a vertex and 1 if outside of the segment. */
template <class T>
int point_inside_segment(const Point<T> &q, const Point<T> &a, const Point<T> &b) {
	// On a vertex.
	if (q == a or q == b) {
		return 0;
	}

	// Degenerate case.
	if (a == b) {
		return 1;
	}

	// General case.
	return point_inside_line(q, a, b) and ((b - a) * (q - a)) > static_cast<T>(0) and ((a - b) * (q - b)) > static_cast<T>(0) ? -1 : 1;
}

/* O(1) - Returns -1 if point Q is inside of the triangle ABC, 0 if its on one of its edges or 1 if its outside of the triangle. */ 
template <class T>
int point_inside_triangle(const Point<T> &q, const Point<T> &a, const Point<T> &b, const Point<T> &c) {
	// On an edge.
	if (point_inside_segment(q, a, b) <= 0 or point_inside_segment(q, b, c) <= 0 or point_inside_segment(q, c, a) <= 0) {
		return 0;
	}

	// Clockwise.
	if (((b - a) ^ (c - a)) < static_cast<T>(0)) {
		return (((b - a) ^ (q - a)) < static_cast<T>(0) and ((c - b) ^ (q - b)) < static_cast<T>(0) and ((a - c) ^ (q - c)) < static_cast<T>(0)) ? -1 : 1;
	}

	// Counter-clockwise.
	return (((b - a) ^ (q - a)) > static_cast<T>(0) and ((c - b) ^ (q - b)) > static_cast<T>(0) and ((a - c) ^ (q - c)) > static_cast<T>(0)) ? -1 : 1;
}

/* O(N) - Computes twice the signed area of a convex or non-convex polygon, being it simple or self-intersecting.
   Expects a polygon either in clockwise or in counter-clockwise order. */
template <class T>
T shoelace(const vector<Point<T>> &p) {
	T ans = static_cast<T>(0);

	for (int i = 0; i < p.size(); i++) {
		ans = ans + (p[i] ^ p[(i + 1) % p.size()]);
	}

	return ans;
}

/* O(N) - Returns true if the points of the given simple polygon are in clockwise order. */ 
template <class T>
bool is_clockwise(const vector<Point<T>> &p) {
	return shoelace(p) < static_cast<T>(0);
}

/* O(1) - Returns true if p[i] is a convex vertex. */
template <class T>
bool is_convex(const vector<Point<T>> &p, const vector<int> &l, const vector<int> &r, int i) {
	return ((p[i] - p[l[i]]) ^ (p[r[i]] - p[l[i]])) > static_cast<T>(0);
}

/* O(1) - Returns true if p[b] is an ear. */
template <class T>
bool is_ear(const vector<Point<T>> &p, const vector<int> &l, const vector<int> &r, int i) {
	// Ear has to be convex.
	if (!is_convex(p, l, r, i)) {
		return false;
	}

	// For each point currently in the polygon, except for l[i], i and r[i].
	for (int j = r[r[i]]; j != l[i]; j = r[j]) {
		// If there's a point inside the triangle (p[l[i]], p[i], p[r[i]]) then p[i] is not an ear.
		if (point_inside_triangle(p[j], p[l[i]], p[i], p[r[i]]) <= 0) {
			return false;
		}
	}

	return true;
}

/* O(N^2) - Returns a triangulation of the given simple polygon. */
template <class T>
vector<vector<Point<T>>> ear_clipping(vector<Point<T>> p) {
	vector<vector<Point<T>>> ans;
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