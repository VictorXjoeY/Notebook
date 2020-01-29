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
	bool operator == (const Point2D &b) const {
		return this->x == b.x and this->y == b.y;
	}

	/* O(1) - Different. */
	bool operator != (const Point2D &b) const {
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
	return static_cast<Point2D<T>>((static_cast<Point3D<U>>(a) ^ static_cast<Point3D<U>>(b)) ^ (static_cast<Point3D<U>>(c) ^ static_cast<Point3D<U>>(d)));
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
	return line_line_intersection<T>(a, b, p, p + rotate90(b - a));
}

/* O(1) - Returns a pair of points (P, Q) such that P belongs to line AB and Q belongs to line CD their distance is minimal. */
template <class T, class U>
pair<Point2D<T>, Point2D<T>> line_line_distance(const Point2D<U> &a, const Point2D<U> &b, const Point2D<U> &c, const Point2D<U> &d) {
	if (line_line_intersects(a, b, c, d) == 1) {
		Point2D<T> q = line_line_intersection<T>(a, b, c, d);
		return {q, q};
	}

	return {a, point_line_distance<T>(c, d, a)};
}