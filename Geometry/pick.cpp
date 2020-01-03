struct Point {
	long long x, y;

	/* O(1) - Cross product. */
	long long operator ^ (const Point &b) const {
		return this->x * b.y - this->y * b.x;
	}
};

/* O(N) - Computes twice the area of a convex or non-convex polygon, being it simple or self-intersecting.
   Expects a polygon either in clockwise or in counter-clockwise order. */
long long shoelace(const vector<Point> &p) {
	long long ans = 0;

	for (int i = 0; i < p.size(); i++) {
		ans += p[i] ^ p[(i + 1) % p.size()];
	}

	return abs(ans);
}

/* O(N * Log(MAX)) - Computes the number of interior points in a simple polygon according to Pick's Theorem: A = i + b / 2 - 1 */
long long interior_points(const vector<Point> &p) {
	long long b = 0;

	for (int i = 0; i < p.size(); i++) {
		b += __gcd(abs(p[(i + 1) % p.size()].y - p[i].y), abs(p[(i + 1) % p.size()].x - p[i].x));
	}

	return (shoelace(p) - b + 2) / 2;
}
