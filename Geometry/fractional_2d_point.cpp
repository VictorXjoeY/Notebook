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

	/* O(1) - Vector sum. */
	Point operator + (const Point &b) const {
		return {this->x + b.x, this->y + b.y};
	}

	/* O(1) - Vector subtraction. */
	Point operator - (const Point &b) const {
		return {this->x - b.x, this->y - b.y};
	}

	/* O(1) - Vector product by scalar. */
	Point operator * (Fraction a) {
		return {this->x * a, this->y * a};
	}

	/* O(1) - Vector division by scalar. */
	Point operator / (Fraction a) {
		return {this->x / a, this->y / a};
	}

	/* O(1) - Dot product. */
	Fraction operator * (const Point &b) const {
		return (this->x * b.x) + (this->y * b.y);
	}

	/* O(1) - Cross product. */
	Fraction operator ^ (const Point &b) const {
		return (this->x * b.y) - (this->y * b.x);
	}

	/* O(1) - Squared norm. */
	Fraction operator ! () const {
		return (this->x * this->x) + (this->y * this->y);
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

	/* O(1) - Compare function. */
	bool operator != (const Point &b) const {
		return !(*this == b);
	}
};