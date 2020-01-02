struct Point {
	long long x, y;

	// Cross product.
	long long operator ^ (const Point &b) const {
		return this->x * b.y - this->y * b.x;
	}
};

/* O(N) - Computes twice the signed area of a convex or non-convex polygon, being it simple or self-intersecting.
   Expects a polygon either in clockwise or in counter-clockwise order. */
long long shoelace(const vector<Point> &p) {
	long long ans = 0;

	for (int i = 0; i < p.size() - 1; i++) {
		ans += p[i] ^ p[i + 1];
	}

	ans += p.back() ^ p[0];

	return ans;
}

/* O(N) - Returns true if the points of the given simple polygon are in clockwise order. */ 
bool is_clockwise(const vector<Point> &p) {
	return shoelace(p) < 0;
}