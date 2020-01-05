template <class T>
struct Point {
	T x, y;

	/* O(1) - Vector subtraction. */
	Point<T> operator - (const Point<T> &b) const {
		return {this->x - b.x, this->y - b.y};
	}

	/* O(1) - Cross product. */
	T operator ^ (const Point<T> &b) const {
		return this->x * b.y - this->y * b.x;
	}
};

/* O(1) - Returns true if point Q is inside triangle ABC or on one of its edges. */ 
template <class T>
bool point_inside_triangle(const Point<T> &q, const Point<T> &a, const Point<T> &b, const Point<T> &c) {
	if (((b - a) ^ (c - a)) < static_cast<T>(0)) { // Clockwise.
		return ((b - a) ^ (q - a)) <= static_cast<T>(0) and ((c - b) ^ (q - b)) <= static_cast<T>(0) and ((a - c) ^ (q - c)) <= static_cast<T>(0);
	}

	// Counter-clockwise.
	return ((b - a) ^ (q - a)) >= static_cast<T>(0) and ((c - b) ^ (q - b)) >= static_cast<T>(0) and ((a - c) ^ (q - c)) >= static_cast<T>(0);
}