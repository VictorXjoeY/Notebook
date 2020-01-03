/* O(Log(min(a, b))). */
long long lcm(long long a, long long b) {
	return (a / __gcd(a, b)) * b;
}

struct Fraction {
	long long num, den; // Always stores the irreducible fraction num / den, such that den is positive.

	/* O(1). */
	Fraction() {
		this->num = 0;
		this->den = 1;
	}

	/* O(Log(min(num, den))). */
	Fraction(long long num_, long long den_) {
		assert(den_ != 0);

		long long g = abs(__gcd(num_, den_));

		if ((num_ >= 0 and den_ > 0) or (num_ < 0 and den_ < 0)) {
			this->num = abs(num_) / g;
		}
		else{
			this->num = -abs(num_) / g;
		}
		
		this->den = abs(den_) / g;
	}

	/* O(1). */
	double to_double() const {
		return this->num / (double)this->den;
	}

	/* O(Log(min(num, den))). */
	Fraction operator + (const Fraction &f) const {
		long long l = lcm(this->den, f.den);
		return Fraction(this->num * (l / this->den) + f.num * (l / f.den), l);
	}

	/* O(Log(min(num, den))). */
	Fraction operator - (const Fraction &f) const {
		long long l = lcm(this->den, f.den);
		return Fraction(this->num * (l / this->den) - f.num * (l / f.den), l);
	}

	/* O(Log(min(num, den))). */
	Fraction operator * (const Fraction &f) const {
		return Fraction(this->num * f.num, this->den * f.den);
	}

	/* O(Log(min(num, den))). */
	Fraction operator / (const Fraction &f) const {
		return Fraction(this->num * f.den, this->den * f.num);
	}

	/* O(1). */
	bool operator < (const Fraction &f) const {
		return this->num * f.den < f.num * this->den;
	}

	/* O(1). */
	bool operator <= (const Fraction &f) const {
		return !(*this > f);
	}

	/* O(1). */
	bool operator > (const Fraction &f) const {
		return f < *this;
	}

	/* O(1). */
	bool operator >= (const Fraction &f) const {
		return !(*this < f);
	}

	/* O(1). */
	bool operator == (const Fraction &f) const {
		return this->num == f.num and this->den == f.den;
	}

	/* O(1). */
	bool operator != (const Fraction &f) const {
		return !(*this == f);
	}
};

struct Point {
	Fraction x, y;

	/* O(1) - Vector subtraction. */
	Point operator - (const Point &b) const {
		return {this->x - b.x, this->y - b.y};
	}

	/* O(1) - Dot product. */
	Fraction operator * (const Point &b) const {
		return (this->x * b.x) + (this->y * b.y);
	}

	/* O(1) - Cross product. */
	Fraction operator ^ (const Point &b) const {
		return (this->x * b.y) - (this->y * b.x);
	}

	/* O(1) - Compare function. */
	bool operator == (const Point &b) const {
		return this->x == b.x and this->y == b.y;
	}
};

/* O(1) - Returns true if the point Q is inside the line defined by AB. */
bool point_inside_line(const Point &q, const Point &a, const Point &b) {
	return ((b - a) ^ (q - a)) == Fraction(0, 1);
}

/* O(1) - Returns true if the point Q is inside the segment AB. */
bool point_inside_segment(const Point &q, const Point &a, const Point &b) {
	return point_inside_line(q, a, b) and ((b - a) * (q - a)) >= Fraction(0, 1) and ((a - b) * (q - b)) >= Fraction(0, 1);
}

/* O(1) - Returns 0 if the lines don't intersect. Returns 1 if the lines intersect at 1 point. Returns 2 if the lines are the same. */
int line_line_intersects(const Point &a, const Point &b, const Point &c, const Point &d) {
	if (a == b and c == d) { // Both are degenerate.
		return b == c; // Returns 1 if the points are the same and 0 otherwise.
	}
	
	if (a == b) { // AB is degenerate.
		return point_inside_line(a, c, d); // Returns 1 if A is in line CD.
	}
	
	if (c == d) { // CD is degenerate.
		return point_inside_line(c, a, b); // Returns 1 if C is in line AB.
	}

	// Parallel lines.
	if (((b - a) ^ (d - c)) == Fraction(0, 1)) {
		return point_inside_line(c, a, b) ? 2 : 0;
	}

	// General case.
	return 1;
}

/* O(1) - Returns the point of intersection between a line defined by AB and a line defined by CD.
   You need to first guarantee that the lines have exactly 1 intersection point.
   Caution with overflowing the Fractions because the numerator and the denominator of the intersection point will be of the order of x^4 and y^4. */
Point line_line_intersection(const Point &a, const Point &b, const Point &c, const Point &d) {
	assert(line_line_intersects(a, b, c, d) == 1); // Guarantees that it has exactly 1 intersection point.

	if (a == b and c == d) { // Both are degenerate.
		return a;
	}
	
	if (a == b) { // AB is degenerate.
		return a;
	}
	
	if (c == d) { // CD is degenerate.
		return c;
	}

	Point ax1 = {a.x, Fraction(1, 1)};
	Point ay1 = {a.y, Fraction(1, 1)};

	Point bx1 = {b.x, Fraction(1, 1)};
	Point by1 = {b.y, Fraction(1, 1)};

	Point cx1 = {c.x, Fraction(1, 1)};
	Point cy1 = {c.y, Fraction(1, 1)};

	Point dx1 = {d.x, Fraction(1, 1)};
	Point dy1 = {d.y, Fraction(1, 1)};

	Point px_num_a = {a ^ b, ax1 ^ bx1};
	Point px_num_b = {c ^ d, cx1 ^ dx1};

	Point py_num_a = {a ^ b, ay1 ^ by1};
	Point py_num_b = {c ^ d, cy1 ^ dy1};

	Point den_a = {ax1 ^ bx1, ay1 ^ by1};
	Point den_b = {cx1 ^ dx1, cy1 ^ dy1};

	return {(px_num_a ^ px_num_b) / (den_a ^ den_b), (py_num_a ^ py_num_b) / (den_a ^ den_b)};
}