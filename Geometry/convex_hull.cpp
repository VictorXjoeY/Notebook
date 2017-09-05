struct Point{
	long long x, y;

	Point(){
		this->x = 0;
		this->y = 0;
	}

	Point(long long x, long long y){
		this->x = x;
		this->y = y;
	}

	bool operator < (const Point& b) const{
		if (this->x == b.x){
			return this->y < b.y;
		}

		return this->x < b.x;
	}
};

long long cross(Point a, Point b){
	return a.x * b.y - a.y * b.x;
}

Point sub(Point a, Point b){
	return Point(a.x - b.x, a.y - b.y);
}

stack<Point> ch;
vector<Point> v;
Point p;

bool comp(Point &a, Point &b){
	// Same angle. Furthest point first.
	if (cross(sub(a, p), sub(b, p)) == 0){
		return b < a;
	}

	return cross(sub(a, p), sub(b, p)) > 0;
}

void convex_hull(){
	Point a, b, c;
	int i;

	// First point belonging to the Convex Hull
	p = *min_element(v.begin(), v.end());
	sort(v.begin(), v.end(), comp);

	ch.push(p);
	ch.push(v[0]);
	ch.push(v[1]);

	for (i = 2; i < (int)v.size(); i++){
		c = v[i];
		b = ch.top();
		ch.pop();
		a = ch.top();

		// While not a left turn
		while (cross(sub(b, a), sub(c, a)) <= 0){
			b = a;
			ch.pop();
			a = ch.top();
		}

		ch.push(b);
		ch.push(c);
	}

	ch.pop();
}