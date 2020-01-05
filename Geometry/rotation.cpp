struct Point {
	double x, y;

	/* O(1) - Vector sum. */
	Point operator + (const Point &b) const {
		return {this->x + b.x, this->y + b.y};
	}

	/* O(1) - Vector subtraction. */
	Point operator - (const Point &b) const {
		return {this->x - b.x, this->y - b.y};
	}
};

/* O(1) - Rotates vector p by theta radians. */
Point rotate(const Point &p, double theta) {
	return {p.x * cos(theta) - p.y * sin(theta), p.x * sin(theta) + p.y * cos(theta)};
}

/* O(1) - Rotates points p around pivot by theta radians. */
Point rotate(const Point &pivot, const Point &p, double theta) {
	return pivot + rotate(p - pivot, theta);
}