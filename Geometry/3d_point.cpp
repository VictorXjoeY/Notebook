struct Point {
	long long x, y, z;

	/* O(1) - Vector sum. */
	Point operator + (const Point &b) const {
		return {this->x + b.x, this->y + b.y, this->z + b.z};
	}

	/* O(1) - Vector sum (cumulative). */
	Point &operator += (const Point &b) {
		this->x += b.x;
		this->y += b.y;
		this->z += b.z;

		return *this;
	}

	/* O(1) - Negative vector. */
	Point operator - () const {
		return {-this->x, -this->y, -this->z};
	}

	/* O(1) - Vector subtraction. */
	Point operator - (const Point &b) const {
		return {this->x - b.x, this->y - b.y, this->z - b.z};
	}

	/* O(1) - Vector subtraction (cumulative). */
	Point &operator -= (const Point &b) {
		this->x -= b.x;
		this->y -= b.y;
		this->z -= b.z;

		return *this;
	}

	/* O(1) - Vector product by scalar. */
	Point operator * (long long a) {
		return {this->x * a, this->y * a, this->z * a};
	}

	/* O(1) - Vector product by scalar (cumulative). */
	Point &operator *= (long long a) {
		this->x *= a;
		this->y *= a;
		this->z *= a;

		return *this;
	}

	/* O(1) - Vector division by scalar. */
	Point operator / (long long a) {
		return {this->x / a, this->y / a, this->z / a};
	}

	/* O(1) - Vector division by scalar (cumulative). */
	Point &operator /= (long long a) {
		this->x /= a;
		this->y /= a;
		this->z /= a;

		return *this;
	}

	/* O(1) - Dot product. */
	long long operator * (const Point &b) const {
		return this->x * b.x + this->y * b.y + this->z * b.z;
	}

	/* O(1) - Cross product. */
	Point operator ^ (const Point &b) const {
		return {this->y * b.z - this->z * b.y, this->z * b.x - this->x * b.z, this->x * b.y - this->y * b.x};
	}

	/* O(1) - Cross product (cumulative). */
	Point &operator ^= (const Point &b) {
		long long new_x, new_y, new_z;

		new_x = this->y * b.z - this->z * b.y;
		new_y = this->z * b.x - this->x * b.z;
		new_z = this->x * b.y - this->y * b.x;

		this->x = new_x;
		this->y = new_y;
		this->z = new_z;

		return *this;
	}

	/* O(1) - Squared norm. */
	long long operator ! () const {
		return this->x * this->x + this->y * this->y + this->z * this->z;
	}

	/* O(1) - Compare function. */
	bool operator < (const Point &b) const {
		if (this->x == b.x) {
			if (this->y == b.y) {
				return this->z < b.z;
			}

			return this->y < b.y;
		}

		return this->x < b.x;
	}

	/* O(1) - Compare function. */
	bool operator > (const Point &b) const {
		return b < *this;
	}

	/* O(1) - Compare function. */
	bool operator == (const Point &b) const {
		return !(*this < b) and !(*this > b);
	}

	/* O(1) - Compare function. */
	bool operator != (const Point &b) const {
		return !(*this == b);
	}
};

/* O(1) - Overloading stream operator in order to print a point. */
ostream& operator << (ostream& out, const Point &p) {
    out << "(" << p.x << ", " << p.y << ", " << p.z << ")";
 
    return out;
}
 
/* O(1) - Overloading stream operator in order to read a point. */
istream& operator >> (istream& in, Point &p) {
    in >> p.x >> p.y >> p.z;
 
    return in;
}
