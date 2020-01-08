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

	/* O(1). */
	Fraction(long long n) {
		this->num = n;
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
	Fraction operator - () const {
		Fraction f;
		f.num = -this->num;
		f.den = this->den;
		return f;
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

	/* O(1). */
	operator double() {
		return this->num / static_cast<double>(this->den);
	}
};

/* O(1). */
Fraction abs(const Fraction &f) {
	return f < Fraction(0) ? -f : f;
}

/* O(1) - String conversion. */
string to_string(const Fraction &f) {
	return to_string(f.num) + "/" + to_string(f.den);
}

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
	bool operator < (const Point &b) const {
		if (this->x == b.x) {
			return this->y < b.y;
		}

		return this->x < b.x;
	}

	/* O(1) - Compare function. */
	bool operator == (const Point &b) const {
		return this->x == b.x and this->y == b.y;
	}
};

/* O(1) - Returns true if the point Q is inside the line defined by AB.
   Expects a non-degenerate line AB. */
template <class T>
bool point_inside_line(const Point<T> &q, const Point<T> &a, const Point<T> &b) {
	return ((b - a) ^ (q - a)) == static_cast<T>(0);
}

/* O(1) - Returns -1 if Q is inside the segment AB, 0 if on a vertex and 1 if outside of the segment. */
template <class T>
int point_inside_segment(const Point<T> &q, const Point<T> &a, const Point<T> &b) {
	// On a vertex.
	if (q == a or q == b) {
		return 0;
	}

	// Degenerate case.
	if (a == b) {
		return 1;
	}

	// General case.
	return point_inside_line(q, a, b) and ((b - a) * (q - a)) > static_cast<T>(0) and ((a - b) * (q - b)) > static_cast<T>(0) ? -1 : 1;
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

/* O(1) - Returns a vector with: 0 points if there's no intersection, 1 point if the segments intersect at 1 point, 2 points if the segments share a segment of points. */
vector<Point> segment_segment_intersection(const Point &a, const Point &b, const Point &c, const Point &d) {
	// No line intersection.
	if (line_line_intersects(a, b, c, d) == 0) {
		return {};
	}

	// 1 line intersection.
	if (line_line_intersects(a, b, c, d) == 1) {
		Point ans = line_line_intersection(a, b, c, d);

		// If the intersection of the two lines is inside the two segments.
		if (point_inside_segment(ans, a, b) <= 0 and point_inside_segment(ans, c, d) <= 0) {
			return {ans};
		}

		return {};
	}

	// Both segments are in the same line.
	vector<Point> ans;
	
	if (point_inside_segment(a, c, d) <= 0) {
		ans.push_back(a);
	}

	if (point_inside_segment(b, c, d) <= 0) {
		ans.push_back(b);
	}

	if (point_inside_segment(c, a, b) <= 0) {
		ans.push_back(c);
	}

	if (point_inside_segment(d, a, b) <= 0) {
		ans.push_back(d);
	}

	sort(ans.begin(), ans.end());
	ans.resize(unique(ans.begin(), ans.end()) - ans.begin());

	return ans;
}