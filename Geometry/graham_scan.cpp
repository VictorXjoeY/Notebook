struct Point{
	long long x, y;

	Point(){}

	Point(long long x, long long y){
		this->x = x;
		this->y = y;
	}

	bool operator < (const Point &b) const{
		if (this->x == b.x){
			return this->y < b.y;
		}

		return this->x < b.x;
	}
};

Point p;

long long cross(const Point &a, const Point &b){
	return a.x * b.y - a.y * b.x;
}

Point sub(const Point &a, const Point &b){
	return Point(a.x - b.x, a.y - b.y);
}

bool comp(const Point &a, const Point &b){
	// Same angle. Closest point first.
	if (cross(sub(a, p), sub(b, p)) == 0){
		return a < b;
	}

	// True if PA -> PB is a left turn.
	return cross(sub(a, p), sub(b, p)) > 0;
}

/* O(N * Log(N)). */
stack<Point> graham_scan(vector<Point> v){
	stack<Point> ch;
	Point a, b, c;

	// Retrieving the pivot P, the first point belonging to the Convex Hull.
	p = *min_element(v.begin(), v.end());

	// Sorting according to angles relative to the pivot P.
	sort(v.begin(), v.end(), comp);

	// Pushing first two points.
	ch.push(v[0]); // Pivot P.
	ch.push(v[1]);

	// Appending points to the Convex Hull one by one.
	for (int i = 2; i < (int)v.size(); i++){
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

	return ch;
}