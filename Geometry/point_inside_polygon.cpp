struct Point {
	long long x, y;

	// Vector subtraction.
	Point operator - (const Point &b) const {
		return {this->x - b.x, this->y - b.y};
	}

	// Dot product.
	long long operator * (const Point &b) const {
		return (this->x * b.x) + (this->y * b.y);
	}

	// Cross product.
	long long operator ^ (const Point &b) const {
		return this->x * b.y - this->y * b.x;
	}

	bool operator < (const Point &b) const {
		if (this->x == b.x) {
			return this->y < b.y;
		}

		return this->x < b.x;
	}
};

/* O(N) - Computes twice the signed area of a convex or non-convex polygon, being it simple or self-intersecting.
   Expects a polygon either in clockwise or in counter-clockwise order. */
long long shoelace(const vector<Point> &p) {
	long long ans = 0;

	for (int i = 0; i < p.size(); i++) {
		ans += p[i] ^ p[(i + 1) % p.size()];
	}

	return ans;
}

/* O(N) - Returns true if the points of the given simple polygon are in clockwise order. */ 
bool is_clockwise(const vector<Point> &p) {
	return shoelace(p) < 0;
}

/* O(1) - Returns true if the point Q is inside the line defined by AB. */
bool point_inside_line(const Point &q, const Point &a, const Point &b) {
	return ((b - a) ^ (q - a)) == 0;
}

/* O(1) - Returns true if the point Q is inside the segment AB. */
bool point_inside_segment(const Point &q, const Point &a, const Point &b) {
	return point_inside_line(q, a, b) and ((b - a) * (q - a)) >= 0 and ((a - b) * (q - b)) >= 0;
}

/* O(N) - Returns true if the point Q is inside the simple polygon P or on one of its edges.
   Expects a polygon either in clockwise or in counter-clockwise order. */
bool point_inside_polygon(const Point &q, vector<Point> p) {
	// Making it counter-clockwise.
	if (is_clockwise(p)) {
		reverse(p.begin(), p.end());
	}
	
	// Pushing back a sentinel.
	p.push_back(p[0]);

	// Checking if the point is on an edge.
	for (int i = 0; i < p.size() - 1; i++) {
		if (point_inside_segment(q, p[i], p[(i + 1) % p.size()])) {
			return true;
		}
	}

	// Winding number.
	int ans = 0;

	// Tracing a ray to the right.
	for (int i = 0; i < p.size() - 1; i++) {
		int a = i;
		int b = i + 1;

		// Making p[a].y <= p[b].y
		if (p[a].y > p[b].y) {
			swap(a, b);
		}

		// If p[a] has y lesser than q.y, p[b] has y greater than q.y and (q, p[a], p[b]) is a left turn, then the ray intersects this edge.
		if (p[a].y < q.y and q.y < p[b].y and ((p[a] - q) ^ (p[b] - q)) > 0) {
			if (a < b) { // Edge going up.
				ans++;
			}
			else { // Edge going down.
				ans--;
			}
		}
	}

	return ans != 0;
}