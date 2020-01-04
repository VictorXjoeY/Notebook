template <class T>
struct Point {
	T x, y;

	/* O(1) - Negative vector. */
	Point operator - () const {
		return {-this->x, -this->y};
	}
	
	/* O(1) - Vector sum. */
	Point operator + (const Point &b) const {
		return {this->x + b.x, this->y + b.y};
	}

	/* O(1) - Vector subtraction. */
	Point operator - (const Point &b) const {
		return {this->x - b.x, this->y - b.y};
	}

	/* O(1) - Dot product. */
	T operator * (const Point &b) const {
		return (this->x * b.x) + (this->y * b.y);
	}

	/* O(1) - Cross product. */
	T operator ^ (const Point &b) const {
		return (this->x * b.y) - (this->y * b.x);
	}

	/* O(1) - Squared norm. */
	T operator ! () const {
		return (this->x * this->x) + (this->y * this->y);
	}

	/* O(1) - Lesser than. */
	bool operator < (const Point &b) const {
		if (this->x == b.x) {
			return this->y < b.y;
		}

		return this->x < b.x;
	}

	/* O(1) - Greater than. */
	bool operator > (const Point &b) const {
		return b < *this;
	}

	/* O(1) - Equal. */
	bool operator == (const Point &b) const {
		return !(*this < b) and !(*this > b);
	}

	/* O(1) - Different. */
	bool operator != (const Point &b) const {
		return !(*this == b);
	}
};

/* O(1) - String conversion. */
template <class T>
string to_string(const Point<T> &p) {
	return "(" + to_string(p.x) + ", " + to_string(p.y) + ")";
}