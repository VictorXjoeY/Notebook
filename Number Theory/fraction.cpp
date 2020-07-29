/* O(Log(min(a, b))). */
long long lcm(long long a, long long b) {
	return (a / __gcd(a, b)) * b;
}

struct Fraction {
	long long num, den; // Always stores the irreducible fraction num / den, such that den is positive.

	/* O(Log(min(num, den))). */
	Fraction(long long num_ = 0, long long den_ = 1) {
		assert(den_ != 0);

		long long g = abs(__gcd(num_, den_));

		if ((num_ >= 0 and den_ > 0) or (num_ < 0 and den_ < 0)) {
			num = abs(num_) / g;
		}
		else{
			num = -abs(num_) / g;
		}
		
		den = abs(den_) / g;
	}

	/* O(1). */
	Fraction operator - () const {
		Fraction f;
		f.num = -num;
		f.den = den;
		return f;
	}

	/* O(1). */
	operator string() const {
		return to_string(num) + "/" + to_string(den);
	}
};

/* O(Log(min(num, den))). */
Fraction operator + (const Fraction &lhs, const Fraction &rhs) {
	long long l = lcm(lhs.den, rhs.den);
	return Fraction(lhs.num * (l / lhs.den) + rhs.num * (l / rhs.den), l);
}

/* O(Log(min(num, den))). */
Fraction operator - (const Fraction &lhs, const Fraction &rhs) {
	long long l = lcm(lhs.den, rhs.den);
	return Fraction(lhs.num * (l / lhs.den) - rhs.num * (l / rhs.den), l);
}

/* O(Log(min(num, den))). */
Fraction operator * (const Fraction &lhs, const Fraction &rhs) {
	return Fraction(lhs.num * rhs.num, lhs.den * rhs.den);
}

/* O(Log(min(num, den))). */
Fraction operator / (const Fraction &lhs, const Fraction &rhs) {
	return Fraction(lhs.num * rhs.den, lhs.den * rhs.num);
}

/* O(1). */
bool operator < (const Fraction &lhs, const Fraction &rhs) {
	return lhs.num * rhs.den < rhs.num * lhs.den;
}

/* O(1). */
bool operator > (const Fraction &lhs, const Fraction &rhs) {
	return rhs < lhs;
}

/* O(1). */
bool operator <= (const Fraction &lhs, const Fraction &rhs) {
	return !(lhs > rhs);
}

/* O(1). */
bool operator >= (const Fraction &lhs, const Fraction &rhs) {
	return !(lhs < rhs);
}

/* O(1). */
bool operator == (const Fraction &lhs, const Fraction &rhs) {
	return lhs.num == rhs.num and lhs.den == rhs.den;
}

/* O(1). */
bool operator != (const Fraction &lhs, const Fraction &rhs) {
	return !(lhs == rhs);
}

/* O(1). */
Fraction abs(const Fraction &f) {
	return f < 0 ? -f : f;
}