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
	operator Point3D<U>() const {
		return {static_cast<U>(this->x), static_cast<U>(this->y), static_cast<U>(1)};
	}
};

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