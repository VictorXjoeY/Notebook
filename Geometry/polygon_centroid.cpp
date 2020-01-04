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
};

/* O(1). */
double to_double(const Fraction &f) {
	return f.num / (double)f.den;
}

/* O(1) - String conversion. */
string to_string(const Fraction &f) {
	return to_string(f.num) + "/" + to_string(f.den);
}

struct Point {
	Fraction x, y;

	/* O(1) - Cross product. */
	Fraction operator ^ (const Point &b) const {
		return this->x * b.y - this->y * b.x;
	}
};

/* O(N) - Computes the area of a convex or non-convex polygon, being it simple or self-intersecting.
   Expects a polygon either in clockwise or in counter-clockwise order. */
Fraction shoelace(const vector<Point> &p) {
	Fraction ans = Fraction(0, 1);

	for (int i = 0; i < p.size(); i++) {
		ans = ans + (p[i] ^ p[(i + 1) % p.size()]);
	}

	// Absolute value.
	if (ans.num < 0) {
		ans.num *= -1;
	}

	return ans / Fraction(2, 1);
}

/* O(N) - Computes the center of mass of a simple polygon.
   Caution with overflowing the Fractions because the numerator is of the order of x^3 and y^3. */
Point centroid(const vector<Point> &p) {
	Point c = {Fraction(0, 1), Fraction(0, 1)};
	Fraction a = shoelace(p);

	for (int i = 0; i < p.size(); i++) {
		c.x = c.x + (p[i].x + p[(i + 1) % p.size()].x) * (p[i] ^ p[(i + 1) % p.size()]);
		c.y = c.y + (p[i].y + p[(i + 1) % p.size()].y) * (p[i] ^ p[(i + 1) % p.size()]);
	}

	a = shoelace(p);
	c.x = c.x / (Fraction(6, 1) * a);
	c.y = c.y / (Fraction(6, 1) * a);

	return c;
}