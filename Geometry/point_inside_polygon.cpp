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
};

/* O(1) - Returns true if the point Q is inside the line defined by AB. */
template <class T>
bool point_inside_line(const Point<T> &q, const Point<T> &a, const Point<T> &b) {
	return ((b - a) ^ (q - a)) == static_cast<T>(0);
}

/* O(1) - Returns true if the point Q is inside the segment AB. */
template <class T>
bool point_inside_segment(const Point<T> &q, const Point<T> &a, const Point<T> &b) {
	return point_inside_line(q, a, b) and ((b - a) * (q - a)) >= static_cast<T>(0) and ((a - b) * (q - b)) >= static_cast<T>(0);
}

/* O(N) - Computes twice the signed area of a convex or non-convex polygon, being it simple or self-intersecting.
   Expects a polygon either in clockwise or in counter-clockwise order. */
template <class T>
T shoelace(const vector<Point<T>> &p) {
	T ans = 0;

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

/* O(N) - Returns true if the point Q is inside the simple polygon P or on one of its edges.
   Expects a polygon either in clockwise or in counter-clockwise order. */
template <class T>
bool point_inside_polygon(const Point<T> &q, vector<Point<T>> p) {
	// Making it counter-clockwise.
	if (is_clockwise(p)) {
		reverse(p.begin(), p.end());
	}
	
	// Pushing back a sentinel.
	p.push_back(p[0]);

	// Checking if the point is on an edge.
	for (int i = 0; i < p.size() - 1; i++) {
		if (point_inside_segment(q, p[i], p[i + 1])) {
			return true;
		}
	}

	// Winding number.
	int wn = 0;

	// Tracing a ray to the right.
	for (int i = 0; i < p.size() - 1; i++) {
		if (p[i].y <= q.y) { // Candidate for upward edge.
			if (q.y < p[i + 1].y and ((p[i] - q) ^ (p[i + 1] - q)) > static_cast<T>(0)) { // Valid upward edge and to the right of Q.
				wn++;
			}
		}
		else { // Candidate for downward edge.
			if (q.y >= p[i + 1].y and ((p[i] - q) ^ (p[i + 1] - q)) < static_cast<T>(0)) { // Valid downward edge and to the right of Q.
				wn--;
			}
		}
	}

	return wn != 0;
}