#define N 100000

struct Point{
	long long x, y;

	Point(){}

	Point(long long x, long long y){
		this->x = x;
		this->y = y;
	}
};

Point p[N + 1];
int n;

/* O(N) - Computes the area of a simple (convex or concave) polygon. */
double shoelace(){
	long long ans;
	int i;

	ans = 0;

	for (i = 1; i < n; i++){
		ans += p[i].x * p[i + 1].y - p[i + 1].x * p[i].y;
	}

	ans += p[n].x * p[1].y - p[1].x * p[n].y;

	return abs(ans) / 2.0;
}