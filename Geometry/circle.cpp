/* The area of the intersection still gives Wrong Answer on https://codeforces.com/contest/600/problem/D */

#define PI 3.14159265358979323846

struct Point{
	double x, y;

	Point(){
		this->x = this->y = 0.0;
	}

	Point(double x, double y){
		this->x = x;
		this->y = y;
	}
};

struct Circle{
	long long x, y, r;

	Circle(){
		this->x = this->y = this->r = 0;
	}

	Circle(long long x, long long y, long long r){
		this->x = x;
		this->y = y;
		this->r = r;
	}
};

Point sum(const Point &a, const Point &b){
	return Point(a.x + b.x, a.y + b.y);
}

Point sub(const Point &a, const Point &b){
	return Point(a.x - b.x, a.y - b.y);
}

Point mul(const Point &a, double x){
	return Point(a.x * x, a.y * x);
}

long long squared_norm(const Point &a){
	return a.x * a.x + a.y * a.y;
}

double norm(const Point &a){
	return sqrt(squared_norm(a));
}

Point rotate(const Point &a, double theta){
	return Point(cos(theta) * a.x - sin(theta) * a.y, sin(theta) * a.x + cos(theta) * a.y);
}

double circle_area(const Circle &c){
	return PI * c.r * c.r;
}

/* Returns the intersection points of 2 DIFFERENT circles. */
vector<Point> circle_circle_intersection_points(Circle circle1, Circle circle2){
	vector<Point> ans;
	Point c1, c2, v;
	double alpha;
	long long d;

	// Making r1 >= r2.
	if (circle1.r < circle2.r){
		swap(circle1, circle2);
	}

	c1 = Point(circle1.x, circle1.y);
	c2 = Point(circle2.x, circle2.y);

	// Squared distance.
	d = squared_norm(sub(c2, c1));

	if ((circle1.r - circle2.r) * (circle1.r - circle2.r) < d and d < (circle1.r + circle2.r) * (circle1.r + circle2.r)){ // 2 intersection points.
		alpha = acos((circle1.r * circle1.r - circle2.r * circle2.r + d) / (2.0 * circle1.r * sqrt(d))); // Angle between d and r1.
		v = mul(sub(c2, c1), circle1.r / norm(sub(c2, c1))); // Vector of size r1: (c2 - c1) * r1 / norm(c2 - c1)
		ans.push_back(sum(c1, rotate(v, alpha))); // c1 + rotate(v, alpha)
		ans.push_back(sum(c1, rotate(v, -alpha))); // c1 + rotate(v, -alpha)
	}
	else if (d == (circle1.r + circle2.r) * (circle1.r + circle2.r) or d == (circle1.r - circle2.r) * (circle1.r - circle2.r)){ // 1 intersection point.
		// c1 + (c2 - c1) * r1 / d.
		ans.push_back(sum(c1, mul(sub(c2, c1), circle1.r / sqrt(d))));
	}

	return ans;
}

/* Returns the intersection area of 2 circles. */
double circle_circle_intersection_area(Circle circle1, Circle circle2){
	double ans, alpha, beta, sectors, triangles;
	Point c1, c2, p1, p2, v;
	long long d;

	// Making r1 >= r2.
	if (circle1.r < circle2.r){
		swap(circle1, circle2);
	}

	c1 = Point(circle1.x, circle1.y);
	c2 = Point(circle2.x, circle2.y);

	// Squared distance.
	d = squared_norm(sub(c2, c1));
	ans = 0.0;

	if ((circle1.r - circle2.r) * (circle1.r - circle2.r) < d and d < (circle1.r + circle2.r) * (circle1.r + circle2.r)){ // 2 intersection points.
		alpha = acos((circle1.r * circle1.r - circle2.r * circle2.r + d) / (2.0 * circle1.r * sqrt(d))); // Angle between d and r1.
		beta = acos((circle2.r * circle2.r - circle1.r * circle1.r + d) / (2.0 * circle2.r * sqrt(d))); // Angle between d and r2.

		sectors = alpha * circle1.r * circle1.r + beta * circle2.r * circle2.r; // Area of sectors.
		triangles = (circle1.r * circle1.r * sin(2.0 * alpha) + circle2.r * circle2.r * sin(2.0 * beta)) / 2.0; // Area of triangles.
		ans = sectors - triangles;
	}
	else if (d == (circle1.r - circle2.r) * (circle1.r - circle2.r)){ // Second circle is completely inside the first circle.
		ans = circle_area(circle2);
	}

	return ans;
}