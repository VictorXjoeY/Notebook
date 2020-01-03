struct Point {
	long long x, y;

	// Cross product.
	long long operator ^ (const Point &b) const {
		return this->x * b.y - this->y * b.x;
	}
};

/* O(N) - Computes the area of a convex or non-convex polygon, being it simple or self-intersecting.
   Expects a polygon either in clockwise or in counter-clockwise order. */
double shoelace(const vector<Point> &p) {
	long long ans = 0;

	for (int i = 0; i < p.size(); i++) {
		ans += p[i] ^ p[(i + 1) % p.size()];
	}

	return abs(ans) / 2.0;
}
