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

	/* O(1) - Vector subtraction. */
	Point2D<T> operator - (const Point2D<T> &b) const {
		return {this->x - b.x, this->y - b.y};
	}

	/* O(1) - Cross product. */
	T operator ^ (const Point2D<T> &b) const {
		return (this->x * b.y) - (this->y * b.x);
	}

	/* O(1) - Equal. */
	bool operator == (const Point2D &b) const {
		return this->x == b.x and this->y == b.y;
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

/* O(1) - Returns 0 if the lines don't intersect. Returns 1 if the lines intersect at 1 point. Returns 2 if the lines are the same. */
template <class T>
int line_line_intersects(const Point2D<T> &a, const Point2D<T> &b, const Point2D<T> &c, const Point2D<T> &d) {
	if (a == b and c == d) { // Both are degenerate.
		return b == c; // Returns 1 if the points are the same and 0 otherwise.
	}
	
	if (a == b) { // AB is degenerate.
		return point_inside_line(a, c, d); // Returns 1 if A is in line CD.
	}
	
	if (c == d) { // CD is degenerate.
		return point_inside_line(c, a, b); // Returns 1 if C is in line AB.
	}

	// Parallel lines.
	if (((b - a) ^ (d - c)) == static_cast<T>(0)) {
		return point_inside_line(c, a, b) ? 2 : 0;
	}

	// General case.
	return 1;
}

/* O(1) - Returns the point of intersection between a line defined by AB and a line defined by CD.
   You need to first guarantee that the lines have exactly 1 intersection point.
   Caution with overflowing the Fractions because the numerator and the denominator of the intersection point will be of the order of x^4 and y^4. */
template <class T, class U>
Point2D<T> line_line_intersection(const Point2D<U> &a, const Point2D<U> &b, const Point2D<U> &c, const Point2D<U> &d) {
	assert(line_line_intersects(a, b, c, d) == 1); // Guarantees that it has exactly 1 intersection point.

	if (a == b and c == d) { // Both are degenerate.
		return static_cast<Point2D<T>>(a);
	}
	
	if (a == b) { // AB is degenerate.
		return static_cast<Point2D<T>>(a);
	}
	
	if (c == d) { // CD is degenerate.
		return static_cast<Point2D<T>>(c);
	}

	return static_cast<Point2D<T>>((static_cast<Point3D<U>>(a) ^ static_cast<Point3D<U>>(b)) ^ (static_cast<Point3D<U>>(c) ^ static_cast<Point3D<U>>(d)));
}