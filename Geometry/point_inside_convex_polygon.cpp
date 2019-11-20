struct Point {
	long long x, y;

	// Vector subtraction.
	Point operator - (const Point &b) const {
		return {this->x - b.x, this->y - b.y};
	}

	// Cross product.
	long long operator ^ (const Point &b) const {
		return this->x * b.y - this->y * b.x;
	}

	bool operator < (const Point &b) const {
		if (this->x == b.x) {
			return this->y < b.y;
		}

		return this->x < b.x;
	}
};

Point pivot;

/* O(1) - Compares points A and B using their angle relative to the Pivot. */
bool comp(const Point &a, const Point &b) {
	// Same angle. Closest point first.
	if (((a - pivot) ^ (b - pivot)) == 0) {
		return a < b;
	}

	// True if PA -> PB is a left turn.
	return ((a - pivot) ^ (b - pivot)) > 0;
}

/* O(N * Log(N)) - Sorts the points in a convex polygon in counter-clockwise order. */
void sort_convex_polygon(vector<Point> &p) {
	int i;

	// Retrieving a pivot point.
	pivot = *min_element(p.begin(), p.end());

	// Sorting according to angles relative to the pivot.
	sort(p.begin(), p.end(), comp);

	// Reversing last collinear part.
	for (i = (int)p.size() - 2; i >= 1; i--) {
		if (((p.back() - pivot) ^ (p[i] - pivot)) != 0) {
			break;
		}
	}

	reverse(p.begin() + i + 1, p.end());
}

/* O(1) - Returns true if point Q is inside triangle ABC or on one of its edges. */ 
bool point_inside_triangle(const Point &q, const Point &a, const Point &b, const Point &c) {
	return (((b - a) ^ (q - a)) >= 0 and ((c - b) ^ (q - b)) >= 0 and ((a - c) ^ (q - c)) >= 0) or (((b - a) ^ (q - a)) <= 0 and ((c - b) ^ (q - b)) <= 0 and ((a - c) ^ (q - c)) <= 0);
}

/* O(Log(N)) - Returns true if point Q is inside polygon P. */
bool point_inside_convex_polygon(const Point &q, const vector<Point> &p) {
	int l, r, m;

	// Retrieving the last point p[x] in P such that (p[0], p[x], q) is not a right turn.
	l = 1;
	r = (int)p.size() - 2;

	while (l < r) {
		m = (l + r + 1) / 2;

		if (((p[m] - p[0]) ^ (q - p[0])) >= 0) {
			l = m;
		}
		else{
			r = m - 1;
		}
	}

	return point_inside_triangle(q, p[0], p[l], p[l + 1]);
}

/* O(N * Log(N)) - Sorts the polygon so that we can do a binary search for the queries. */
void init(vector<Point> &p) {
	sort_convex_polygon(p);
}
