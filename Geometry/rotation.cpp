// T must be a floating point type for the rotations to work as intended.
template <class T>
struct Point {
	T x, y;

	/* O(1) - Vector sum. */
	Point<T> operator + (const Point<T> &b) const {
		return {this->x + b.x, this->y + b.y};
	}

	/* O(1) - Vector subtraction. */
	Point<T> operator - (const Point<T> &b) const {
		return {this->x - b.x, this->y - b.y};
	}
};

/* O(1) - Rotates vector p by theta radians. */
template <class T>
Point<T> rotate(const Point<T> &p, double theta) {
	return {p.x * cos(theta) - p.y * sin(theta), p.x * sin(theta) + p.y * cos(theta)};
}

/* O(1) - Rotates points p around pivot by theta radians. */
template <class T>
Point<T> rotate(const Point<T> &pivot, const Point<T> &p, double theta) {
	return pivot + rotate(p - pivot, theta);
}

/* O(N) - Rotates a polygon p around pivot by theta radians. */
template <class T>
vector<Point<T>> rotate(const Point<T> &pivot, const vector<Point<T>> &p, double theta) {
	vector<Point<T>> ans(p.size());

	for (int i = 0; i < p.size(); i++) {
		ans[i] = rotate(pivot, p[i], theta);
	}

	return ans;
}