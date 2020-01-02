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
	Fraction(long long num, long long den) {
		assert(den != 0);

		long long g = abs(__gcd(num, den));

		if ((num >= 0 and den > 0) or (num < 0 and den < 0)) {
			this->num = abs(num) / g;
		}
		else{
			this->num = -abs(num) / g;
		}
		
		this->den = abs(den) / g;
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

	// Vector sum.
	Point operator + (const Point &b) const {
		return {this->x + b.x, this->y + b.y};
	}

	// Vector subtraction.
	Point operator - (const Point &b) const {
		return {this->x - b.x, this->y - b.y};
	}

	// Vector product by scalar.
	Point operator * (Fraction a) {
		return {this->x * a, this->y * a};
	}

	// Vector division by scalar.
	Point operator / (Fraction a) {
		return {this->x / a, this->y / a};
	}

	// Dot product.
	Fraction operator * (const Point &b) const {
		return (this->x * b.x) + (this->y * b.y);
	}

	// Cross product.
	Fraction operator ^ (const Point &b) const {
		return (this->x * b.y) - (this->y * b.x);
	}

	// Squared norm.
	Fraction operator ! () const {
		return (this->x * this->x) + (this->y * this->y);
	}

	// Compare function.
	bool operator < (const Point &b) const {
		if (this->x == b.x) {
			return this->y < b.y;
		}

		return this->x < b.x;
	}

	// Compare function.
	bool operator == (const Point &b) const {
		return this->x == b.x and this->y == b.y;
	}

	// Compare function.
	bool operator != (const Point &b) const {
		return !(*this == b);
	}
};