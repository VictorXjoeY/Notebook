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