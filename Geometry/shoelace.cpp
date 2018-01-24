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

double shoelace(){
	long long ans;
	int i;

	ans = 0;

	for (i = 1; i < n; i++){
		ans += x[i] * y[i + 1] - x[i + 1] * y[i];
	}

	ans += x[n] * y[1] - x[1] * y[n];

	return abs(ans) / 2.0;
}