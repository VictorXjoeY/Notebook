struct Point{
	long long x, y;

	Point(){}

	Point(long long x_, long long y_){
		this->x = x_;
		this->y = y_;
	}
};

/* O(N) - Computes the area of a simple (convex or concave) polygon. */
double shoelace(const vector<Point> &p){
	long long ans;

	ans = 0;

	for (int i = 0; i < (int)p.size() - 1; i++){
		ans += p[i].x * p[i + 1].y - p[i + 1].x * p[i].y;
	}

	ans += p.back().x * p[0].y - p[0].x * p.back().y;

	return abs(ans) / 2.0;
}