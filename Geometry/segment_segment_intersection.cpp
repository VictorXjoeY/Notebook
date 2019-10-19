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
};

/* O(1) - Extracts the sign of x. */
int sign(long long x){
	if (x < 0){
		return -1;
	}

	if (x > 0){
		return 1;
	}

	return 0;
}

/* O(1) - Returns true if the segment AB has any points in common with the segment CD. */
bool segment_segment_intersects(const Point &a, const Point &b, const Point &c, const Point &d){
	// If C is to the opposite side of D relative to the line AB and A is to the opposite side of B relative to line CD.
	return sign((b - a) ^ (c - a)) * sign((b - a) ^ (d - a)) <= 0 and sign((d - c) ^ (a - c)) * sign((d - c) ^ (b - c)) <= 0;
}