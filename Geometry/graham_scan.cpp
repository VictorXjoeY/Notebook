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
	// Same angle. Closest point first.
	if (cross(sub(a, p), sub(b, p)) == 0){
		return a < b;
	}

	// True if PA -> PB is a left turn.
	return cross(sub(a, p), sub(b, p)) > 0;
}

/* O(N * log(N)). */
void graham_scan(){
	Point a, b, c;
	int i;

	// Retrieving the pivot P, the first point belonging to the Convex Hull.
	p = *min_element(v.begin(), v.end());

	// Sorting according to angles relative to the pivot P.
	sort(v.begin(), v.end(), comp);

	// Pushing first two points.
	ch.push(v[0]); // Pivot P.
	ch.push(v[1]);

	// Appending points to the Convex Hull one by one.
	for (i = 2; i < (int)v.size(); i++){
		c = v[i];

		// There are always at least 2 points in the stack in this point.
		do{
			// Retrieving the top 2 from stack (A and B).
			b = ch.top();
			ch.pop();
			a = ch.top();
			ch.pop();

			// If it is a left turn, the three points belong to the current Convex Hull.
			if (cross(sub(b, a), sub(c, a)) > 0){
				// Pushing back A and B.
				ch.push(a);
				ch.push(b);
				break;
			}

			// Not a left turn. Removing B by only pushing back A.
			ch.push(a);
		}while (ch.size() >= 2);

		// Appending C.
		ch.push(c);
	}
}