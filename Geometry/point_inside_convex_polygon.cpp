template <class T>
struct Point {
	T x, y;

	/* O(1) - Vector subtraction. */
	Point<T> operator - (const Point<T> &b) const {
		return {this->x - b.x, this->y - b.y};
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
};

/* O(N * Log(N)) - Sorts the points in a convex polygon in counter-clockwise order. */
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

/* O(1) - Returns true if point Q is inside triangle ABC or on one of its edges. */ 
template <class T>
bool point_inside_triangle(const Point<T> &q, const Point<T> &a, const Point<T> &b, const Point<T> &c) {
	if (((b - a) ^ (c - a)) < static_cast<T>(0)) { // Clockwise.
		return ((b - a) ^ (q - a)) <= static_cast<T>(0) and ((c - b) ^ (q - b)) <= static_cast<T>(0) and ((a - c) ^ (q - c)) <= static_cast<T>(0);
	}

	// Counter-clockwise.
	return ((b - a) ^ (q - a)) >= static_cast<T>(0) and ((c - b) ^ (q - b)) >= static_cast<T>(0) and ((a - c) ^ (q - c)) >= static_cast<T>(0);
}

/* O(Log(N)) - Returns true if the point Q is inside the convex polygon P or on one of its edges.
   Expects a convex polygon in counter-clockwise order. */
template <class T>
bool point_inside_convex_polygon(const Point<T> &q, const vector<Point<T>> &p) {
	int l, r, m;

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

	return point_inside_triangle(q, p[0], p[l], p[l + 1]);
}

/* O(N * Log(N)) - Sorts the polygon so that we can do a binary search for the queries. */
template <class T>
void init(vector<Point<T>> &p) {
	sort_convex_polygon(p);
}