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