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

	// Dot product.
	long long operator * (const Point &b) const{
		return this->x * b.x + this->y * b.y;
	}
};

/* O(1) - Returns true if the point Q is inside the segment AB. */
bool point_inside_segment(const Point &q, const Point &a, const Point &b){
	return ((b - a) ^ (q - a)) == 0 and ((b - a) * (q - a)) >= 0 and ((a - b) * (q - b)) >= 0;
}