#define N 100000

struct Point{
	long long x, y;

	Point(){}

	Point(long long x_, long long y_){
		this->x = x_;
		this->y = y_;
	}
};

Point p[N + 1]; // (Input)
int n; // (Input)

/* O(N) - Computes the area of a simple (convex or concave) polygon. */
double shoelace(){
	long long ans;

	ans = 0;

	for (int i = 1; i < n; i++){
		ans += p[i].x * p[i + 1].y - p[i + 1].x * p[i].y;
	}

	ans += p[n].x * p[1].y - p[1].x * p[n].y;

	return abs(ans) / 2.0;
}