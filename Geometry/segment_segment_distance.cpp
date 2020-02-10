template <class T>
class Point2D;

template <class T>
struct Point3D {
	T x, y, z;
	
	/* O(1) - Cross product. */
	Point3D<T> operator ^ (const Point3D<T> &b) const {
		return {(this->y * b.z) - (this->z * b.y), (this->z * b.x) - (this->x * b.z), (this->x * b.y) - (this->y * b.x)};
	}

	/* O(1). */
	template <class U>
	operator Point2D<U>() const {
		return {static_cast<U>(this->x) / static_cast<U>(this->z), static_cast<U>(this->y) / static_cast<U>(this->z)};
	}
};

template <class T>
struct Point2D {
	T x, y;

	/* O(1) - Vector sum. */
	Point2D<T> operator + (const Point2D<T> &b) const {
		return {this->x + b.x, this->y + b.y};
	}

	/* O(1) - Vector subtraction. */
	Point2D<T> operator - (const Point2D<T> &b) const {
		return {this->x - b.x, this->y - b.y};
	}

	/* O(1) - Dot product. */
	T operator * (const Point2D<T> &b) const {
		return (this->x * b.x) + (this->y * b.y);
	}

	/* O(1) - Cross product. */
	T operator ^ (const Point2D<T> &b) const {
		return (this->x * b.y) - (this->y * b.x);
	}

	/* O(1) - Squared norm. */
	T operator ! () const {
		return (this->x * this->x) + (this->y * this->y);
	}

	/* O(1) - Lesser than. */
	bool operator < (const Point2D<T> &b) const {
		if (this->x == b.x) {
			return this->y < b.y;
		}

		return this->x < b.x;
	}

	/* O(1) - Equal. */
	bool operator == (const Point2D<T> &b) const {
		return this->x == b.x and this->y == b.y;
	}

	/* O(1) - Different. */
	bool operator != (const Point2D<T> &b) const {
		return !(*this == b);
	}

	/* O(1). */
	template <class U>
	operator Point2D<U>() const {
		return {static_cast<U>(this->x), static_cast<U>(this->y)};
	}

	/* O(1). */
	template <class U>
	operator Point3D<U>() const {
		return {static_cast<U>(this->x), static_cast<U>(this->y), static_cast<U>(1)};
	}
};

/* O(1) - Returns true if the point Q is inside the line defined by AB. */
template <class T>
bool point_inside_line(const Point2D<T> &q, const Point2D<T> &a, const Point2D<T> &b) {
	return ((b - a) ^ (q - a)) == static_cast<T>(0);
}

/* O(1) - Returns -1 if Q is inside the segment AB, 0 if on a vertex and 1 if outside of the segment. */
template <class T>
int point_inside_segment(const Point2D<T> &q, const Point2D<T> &a, const Point2D<T> &b) {
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

/* O(1) - Returns 0 if the lines don't intersect. Returns 1 if the lines intersect at 1 point. Returns 2 if the lines are the same.
   Expects non-degenerate lines. */
template <class T>
int line_line_intersects(const Point2D<T> &a, const Point2D<T> &b, const Point2D<T> &c, const Point2D<T> &d) {
	assert(a != b and c != d); // Can't have degenerate lines.

	// Parallel lines.
	if (((b - a) ^ (d - c)) == static_cast<T>(0)) {
		return point_inside_line(c, a, b) ? 2 : 0;
	}

	// General case.
	return 1;
}

/* O(1) - Returns the point of intersection between a line defined by AB and a line defined by CD.
   Expects non-degenerate lines that have exactly 1 intersection point.
   Caution with overflowing the Fractions because the numerator and the denominator of the intersection point will be of the order of x^4 and y^4. */
template <class T, class U>
Point2D<T> line_line_intersection(const Point2D<U> &a, const Point2D<U> &b, const Point2D<U> &c, const Point2D<U> &d) {
	assert(line_line_intersects(a, b, c, d) == 1); // Guarantees that it has exactly 1 intersection point.
	return static_cast<Point2D<T>>((static_cast<Point3D<U>>(a) ^ static_cast<Point3D<U>>(b)) ^ (static_cast<Point3D<U>>(c) ^ static_cast<Point3D<U>>(d)));
}

/* O(1) - Returns a vector with: 0 points if there's no intersection, 1 point if the segments intersect at 1 point, 2 points if the segments share a segment of points. */
template <class T, class U>
vector<Point2D<T>> segment_segment_intersection(const Point2D<U> &a, const Point2D<U> &b, const Point2D<U> &c, const Point2D<U> &d) {
	// Degenerate case.
	if (a == b) {
		if (point_inside_segment(a, c, d) <= 0) {
			return {static_cast<Point2D<T>>(a)};
		}

		return {};
	}

	// Degenerate case.
	if (c == d) {
		if (point_inside_segment(c, a, b) <= 0) {
			return {static_cast<Point2D<T>>(c)};
		}

		return {};
	}

	// No line intersection.
	if (line_line_intersects(a, b, c, d) == 0) {
		return {};
	}

	// 1 line intersection.
	if (line_line_intersects(a, b, c, d) == 1) {
		Point2D<T> ans = line_line_intersection<T>(a, b, c, d);

		// If the intersection of the two lines is inside the two segments.
		if (point_inside_segment(ans, static_cast<Point2D<T>>(a), static_cast<Point2D<T>>(b)) <= 0 and point_inside_segment(ans, static_cast<Point2D<T>>(c), static_cast<Point2D<T>>(d)) <= 0) {
			return {ans};
		}

		return {};
	}

	// Both segments are in the same line.
	vector<Point2D<T>> ans;
	
	if (point_inside_segment(a, c, d) <= 0) {
		ans.push_back(static_cast<Point2D<T>>(a));
	}

	if (point_inside_segment(b, c, d) <= 0) {
		ans.push_back(static_cast<Point2D<T>>(b));
	}

	if (point_inside_segment(c, a, b) <= 0) {
		ans.push_back(static_cast<Point2D<T>>(c));
	}

	if (point_inside_segment(d, a, b) <= 0) {
		ans.push_back(static_cast<Point2D<T>>(d));
	}

	sort(ans.begin(), ans.end());
	ans.resize(unique(ans.begin(), ans.end()) - ans.begin());

	return ans;
}

/* O(1) - Rotates vector p by 90 degrees. */
template <class T>
Point2D<T> rotate90(const Point2D<T> &p) {
	return {-p.y, p.x};
}

/* O(1) - Returns a point Q, the point in line AB closest to point P.
   Expects a non-degenerate line. */
template <class T, class U>
Point2D<T> point_line_distance(const Point2D<U> &a, const Point2D<U> &b, const Point2D<U> &p) {
	assert(a != b); // Can't have a degenerate line.
	return line_line_intersection<T>(a, b, p, p + rotate90(b - a));
}

/* O(1) - Returns a point Q, the point in segment AB closest to point P. */
template <class T, class U>
Point2D<T> point_segment_distance(const Point2D<U> &a, const Point2D<U> &b, const Point2D<U> &p) {
	// Degenerate case.
	if (a == b) {
		return static_cast<Point2D<T>>(a);
	}

	Point2D<T> q = point_line_distance<T>(a, b, p);

	// The closest point is the middle point of this sorted vector.
	vector<Point2D<T>> ans = {static_cast<Point2D<T>>(a), static_cast<Point2D<T>>(b), q};
	sort(ans.begin(), ans.end());

	return ans[1];
}

/* O(1) - Squared distance between two points. Forced to be double because of the high risk of overflow. */
template <class T, class U>
double dist(const Point2D<T> &a, const Point2D<U> &b) {
	return !(static_cast<Point2D<double>>(b) - static_cast<Point2D<double>>(a));
}

/* O(1) - Returns a pair of points (P, Q) such that P belongs to segment AB and Q belongs to segment CD their distance is minimal. */
template <class T, class U>
pair<Point2D<T>, Point2D<T>> segment_segment_distance(const Point2D<U> &a, const Point2D<U> &b, const Point2D<U> &c, const Point2D<U> &d) {
	vector<Point2D<T>> inter = segment_segment_intersection<T>(a, b, c, d);

	if (!inter.empty()) {
		return {inter[0], inter[0]};
	}

	// Calculating all the point-segment distances.
	Point2D<T> ra = point_segment_distance<T>(c, d, a);
	Point2D<T> rb = point_segment_distance<T>(c, d, b);
	Point2D<T> rc = point_segment_distance<T>(a, b, c);
	Point2D<T> rd = point_segment_distance<T>(a, b, d);
	
	vector<pair<Point2D<T>, Point2D<T>>> ans = {{static_cast<Point2D<T>>(a), ra}, {static_cast<Point2D<T>>(b), rb}, {static_cast<Point2D<T>>(c), rc}, {static_cast<Point2D<T>>(d), rd}};

	/* O(1) - Compares pairs of points by their distance. */
	function<bool(const pair<Point2D<T>, Point2D<T>>, const pair<Point2D<T>, Point2D<T>>)> comp = [] (const pair<Point2D<T>, Point2D<T>> &ca, const pair<Point2D<T>, Point2D<T>> &cb) {
		return dist(ca.first, ca.second) < dist(cb.first, cb.second);
	};

	sort(ans.begin(), ans.end(), comp);

	// Returning the pair of points which have the smallest distance between them.
	return ans[0];
}