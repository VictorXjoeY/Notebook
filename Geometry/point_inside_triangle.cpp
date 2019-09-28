struct Point{
	long long x, y;

	Point(){}

	Point(long long x_, long long y_){
		this->x = x_;
		this->y = y_;
	}

	// Vector subtraction.
	Point operator - (const Point &b) const{
		return Point(this->x - b.x, this->y - b.y);
	}

	// Cross product.
	long long operator ^ (const Point &b) const{
		return this->x * b.y - this->y * b.x;
	}
};

/* O(1) - Returns true if point Q is inside triangle ABC or on one of its edges. */ 
bool point_inside_triangle(const Point &q, const Point &a, const Point &b, const Point &c){
	return (((b - a) ^ (q - a)) >= 0 and ((c - b) ^ (q - b)) >= 0 and ((a - c) ^ (q - c)) >= 0) or (((b - a) ^ (q - a)) <= 0 and ((c - b) ^ (q - b)) <= 0 and ((a - c) ^ (q - c)) <= 0);
}