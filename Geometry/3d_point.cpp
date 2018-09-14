struct Point{
	long long x, y, z;

	// Empty constructor.
	Point(){
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	// Constructor.
	Point(long long x, long long y, long long z){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	// Vector sum.
	Point operator + (const Point &b) const{
		return Point(this->x + b.x, this->y + b.y, this->z + b.z);
	}

	// Vector sum (cumulative).
	Point &operator += (const Point &b){
		this->x += b.x;
		this->y += b.y;
		this->z += b.z;

		return *this;
	}

	// Vector subtraction.
	Point operator - (const Point &b) const{
		return Point(this->x - b.x, this->y - b.y, this->z - b.z);
	}

	// Negative vector.
	Point operator - () const{
		return Point(-this->x, -this->y, -this->z);
	}

	// Vector subtraction (cumulative).
	Point &operator -= (const Point &b){
		this->x -= b.x;
		this->y -= b.y;
		this->z -= b.z;

		return *this;
	}

	// Vector product by scalar.
	Point operator * (long long a){
		return Point(this->x * a, this->y * a, this->z * a);
	}

	// Vector product by scalar (cumulative).
	Point &operator *= (long long a){
		this->x *= a;
		this->y *= a;
		this->z *= a;

		return *this;
	}

	// Vector division by scalar.
	Point operator / (long long a){
		return Point(this->x / a, this->y / a, this->z / a);
	}

	// Vector division by scalar (cumulative).
	Point &operator /= (long long a){
		this->x /= a;
		this->y /= a;
		this->z /= a;

		return *this;
	}

	// Dot product.
	long long operator * (const Point &b) const{
		return this->x * b.x + this->y * b.y + this->z * b.z;
	}

	// Cross product.
	Point operator ^ (const Point &b) const{
		return Point(this->y * b.z - this->z * b.y, this->z * b.x - this->x * b.z, this->x * b.y - this->y * b.x);
	}

	// Cross product (cumulative).
	Point &operator ^= (const Point &b){
		long long new_x, new_y, new_z;

		new_x = this->y * b.z - this->z * b.y;
		new_y = this->z * b.x - this->x * b.z;
		new_z = this->x * b.y - this->y * b.x;

		this->x = new_x;
		this->y = new_y;
		this->z = new_z;

		return *this;
	}

	// Squared norm.
	long long operator ! () const{
		return this->x * this->x + this->y * this->y + this->z * this->z;
	}

	// Compare function.
	bool operator < (const Point &b) const{
		if (this->x == b.x){
			if (this->y == b.y){
				return this->z < b.z;
			}

			return this->y < b.y;
		}

		return this->x < b.x;
	}

	// Compare function.
	bool operator > (const Point &b) const{
		return b < *this;
	}

	// Compare function.
	bool operator == (const Point &b) const{
		return !(*this < b) and !(*this > b);
	}

	// Compare function.
	bool operator != (const Point &b) const{
		return !(*this == b);
	}
};

// Overloading stream operator in order to print a point.
ostream& operator << (ostream& out, const Point &p){
    out << "(" << p.x << ", " << p.y << ", " << p.z << ")";
 
    return out;
}
 
// Overloading stream operator in order to read a point.
istream& operator >> (istream& in, Point &p){
    in >> p.x >> p.y >> p.z;
 
    return in;
}