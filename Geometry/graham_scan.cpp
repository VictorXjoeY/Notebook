struct Point{
	long long x, y;

	// Vector subtraction.
	Point operator - (const Point &b) const{
		return {this->x - b.x, this->y - b.y};
	}

	// Cross product.
	long long operator ^ (const Point &b) const{
		return this->x * b.y - this->y * b.x;
	}

	bool operator < (const Point &b) const{
		if (this->x == b.x){
			return this->y < b.y;
		}

		return this->x < b.x;
	}

	bool operator == (const Point &b) const{
		return this->x == b.x and this->y == b.y;
	}
};

Point pivot;

/* O(1) - Compares points A and B using their angle relative to the Pivot. */
bool comp(const Point &a, const Point &b){
	// Same angle. Closest point first.
	if (((a - pivot) ^ (b - pivot)) == 0){
		return a < b;
	}

	// True if PA -> PB is a left turn.
	return ((a - pivot) ^ (b - pivot)) > 0;
}

/* O(N * Log(N)) - Sorts the points in a convex polygon in counter-clockwise order. */
void sort_convex_polygon(vector<Point> &p){
	int i;

	// Retrieving a pivot point.
	pivot = *min_element(p.begin(), p.end());

	// Sorting according to angles relative to the pivot.
	sort(p.begin(), p.end(), comp);

	// Reversing last collinear part.
	for (i = (int)p.size() - 2; i >= 1; i--){
		if (((p.back() - pivot) ^ (p[i] - pivot)) != 0){
			break;
		}
	}

	reverse(p.begin() + i + 1, p.end());
}

/* O(N * Log(N)) - Returns the Convex Hull of a set of points. Expects at least one point. */
vector<Point> graham_scan(vector<Point> p){
	vector<Point> ch; // "Stack"
	Point a, b, c;

	// Sorting and removing repeated points.
	sort_convex_polygon(p);
	p.resize(unique(p.begin(), p.end()) - p.begin());

	// Convex Hull of only one point.
	if (p.size() == 1){
		ch.push_back(p[0]);
		return ch;
	}

	// Convex Hull of only collinear points.
	if (((p[1] - p[0]) ^ (p.back() - p[0])) == 0){
		ch.push_back(p[0]);
		ch.push_back(p[1]);
		return ch;
	}

	// Pushing an extra Pivot as a sentinel.
	p.push_back(pivot);

	// Pushing first two points.
	ch.push_back(p[0]); // Pivot.
	ch.push_back(p[1]);

	// Appending points to the Convex Hull one by one.
	for (int i = 2; i < p.size(); i++){
		c = p[i];

		// There are always at least 2 points in the stack at this point.
		do{
			// Retrieving the top 2 from stack (A and B).
			b = ch.back();
			ch.pop_back();
			a = ch.back();
			ch.pop_back();

			// If it is a left turn, the three points belong to the current Convex Hull.
			if (((b - a) ^ (c - a)) > 0){
				// Pushing back A and B.
				ch.push_back(a);
				ch.push_back(b);
				break;
			}

			// Not a left turn. Removing B by only pushing back A.
			ch.push_back(a);
		}while (ch.size() >= 2);

		// Appending C.
		ch.push_back(c);
	}

	// Removing the Pivot initially pushed as a sentinel.
	ch.pop_back();

	return ch;
}