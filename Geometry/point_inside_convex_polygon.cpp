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

	/* O(1) - Compare function. */
	bool operator < (const Point<T> &b) const {
		if (this->x == b.x) {
			return this->y < b.y;
		}

		return this->x < b.x;
	}

	/* O(1) - Equal. */
	bool operator == (const Point &b) const {
		return this->x == b.x and this->y == b.y;
	}
};

/* O(N * Log(N)) - Sorts the points in an almost convex polygon in counter-clockwise order. */
template <class T>
void sort_convex_polygon(vector<Point<T>> &p) {
	int i;

	// Retrieving a pivot point.
	Point<T> pivot = *min_element(p.begin(), p.end());

	/* O(1) - Compares points A and B using their angle relative to the Pivot. */
	function<bool(const Point<T>, const Point<T>)> comp = [&pivot] (const Point<T> &a, const Point<T> &b) {
		// Same angle. Closest point first.
		if (((a - pivot) ^ (b - pivot)) == static_cast<T>(0)) {
			return a < b;
		}

		// True if PA -> PB is a left turn.
		return ((a - pivot) ^ (b - pivot)) > static_cast<T>(0);
	};

	// Sorting according to angles relative to the pivot.
	sort(p.begin(), p.end(), comp);

	// Reversing last collinear part.
	for (i = (int)p.size() - 2; i >= 1; i--) {
		if (((p.back() - pivot) ^ (p[i] - pivot)) != static_cast<T>(0)) {
			break;
		}
	}

	reverse(p.begin() + i + 1, p.end());
}

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

/* O(Log(N)) - Returns true if the point Q is inside the convex polygon P or on one of its edges.
   Expects an almost convex polygon (such that no other point is collinear with the first edge or the last edge) in counter-clockwise order. */
template <class T>
int point_inside_convex_polygon(const Point<T> &q, const vector<Point<T>> &p) {
	int l, r, m;

	// Degenerate case (only a point).
	if (p.size() == 1) {
		return q == p[0] ? 0 : 1;
	}

	// Degenerate case (every point is collinear).
	if (((p[1] - p[0]) ^ (p.back() - p[0])) == static_cast<T>(0)) {
		return point_inside_segment(q, p[0], p[1]) <= 0 ? 0 : 1;
	}

	// Q is on the first or on the last edge.
	if (point_inside_segment(q, p[0], p[1]) <= 0 or point_inside_segment(q, p[0], p.back()) <= 0) {
		return 0;
	}

	// Retrieving the last point p[x] in P such that (p[0], p[x], q) is not a right turn.
	l = 1;
	r = (int)p.size() - 2;

	while (l < r) {
		m = (l + r + 1) / 2;

		if (((p[m] - p[0]) ^ (q - p[0])) >= static_cast<T>(0)) {
			l = m;
		}
		else{
			r = m - 1;
		}
	}

	// Last "on edge" case.
	if (point_inside_segment(q, p[l], p[l + 1]) <= 0) {
		return 0;
	}

	// General case.
	return point_inside_triangle(q, p[0], p[l], p[l + 1]) < 0 ? -1 : 1;
}

/* O(N * Log(N)) - Transforms the almost convex polygon into a sorted (counter-clockwise) almost convex polygon such that no other point is collinear with the first edge or the last edge. */
template <class T>
void init(vector<Point<T>> &p) {
	sort_convex_polygon(p);

	// Compressing the first collinear part.
	for (int i = 2; i < p.size(); i++) {
		if (((p[1] - p[0]) ^ (p[i] - p[0])) != static_cast<T>(0)) {
			p.erase(p.begin() + 1, p.begin() + i - 1);
			break;
		}
	}

	// Compressing the last collinear part.
	for (int i = p.size() - 2; i >= 1; i--) {
		if (((p.back() - p[0]) ^ (p[i] - p[0])) != static_cast<T>(0)) {
			p.erase(p.begin() + i + 2, p.end());
			break;
		}
	}
}