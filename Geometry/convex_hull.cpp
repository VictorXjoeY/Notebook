struct Point{
	int x, y;

	// Empty constructor.
	Point(){
		this->x = 0;
		this->y = 0;
	}

	// Constructor.
	Point(int x, int y){
		this->x = x;
		this->y = y;
	}

	// Vector sum.
	Point operator + (const Point& b) const{
		return Point(this->x + b.x, this->y + b.y);
	}

	// Vector sum (cumulative).
	Point& operator += (const Point& b){
		this->x += b.x;
		this->y += b.y;

		return *this;
	}

	// Vector subtraction.
	Point operator - (const Point& b) const{
		return Point(this->x - b.x, this->y - b.y);
	}

	// Negative vector.
	Point operator - () const{
		return Point(-this->x, -this->y);
	}

	// Vector subtraction (cumulative).
	Point& operator -= (const Point& b){
		this->x -= b.x;
		this->y -= b.y;

		return *this;
	}

	// Vector product by scalar.
	Point operator * (int a){
		return Point(this->x * a, this->y * a);
	}

	// Vector product by scalar (cumulative).
	Point& operator *= (int a){
		this->x *= a;
		this->y *= a;

		return *this;
	}

	// Vector division by scalar.
	Point operator / (int a){
		return Point(this->x / a, this->y / a);
	}

	// Vector division by scalar (cumulative).
	Point& operator /= (int a){
		this->x /= a;
		this->y /= a;

		return *this;
	}

	// Dot product.
	int operator * (const Point& b) const{
		return this->x * b.x + this->y * b.y;
	}

	// Cross product.
	int operator ^ (const Point& b) const{
		return this->x * b.y - this->y * b.x;
	}

	// Squared norm.
	int operator ! () const{
		return this->x * this->x + this->y * this->y;
	}

	// Compare function.
	bool operator < (const Point& b) const{
		if (this->x == b.x){
			return this->y < b.y;
		}

		return this->x < b.x;
	}

	// Compare function.
	bool operator > (const Point& b) const{
		return b < *this;
	}

	// Compare function.
	bool operator == (const Point& b) const{
		return this->x == b.x and this->y == b.y;
	}

	// Compare function.
	bool operator != (const Point& b) const{
		return !(*this == b);
	}
};

// Overloading stream operator in order to print a point.
ostream& operator << (ostream& out, const Point& p){
    out << "(" << p.x << ", " << p.y << ")";
 
    return out;
}
 
// Overloading stream operator in order to read a point.
istream& operator >> (istream& in, Point& p){
    in >> p.x >> p.y;
 
    return in;
}

deque <Point> ch;
Point p;

bool angle_compare(const Point& a, const Point& b){
	if (((a - p) ^ (b - p)) == 0){
		return a > b;
	}

	return ((a - p) ^ (b - p)) > 0;
}

void convex_hull(){
	Point a, b, c;
	int i;

	p = *min_element(v.begin(), v.end());

	sort(v.begin(), v.end(), angle_compare);

	ch.push_back(p);
	ch.push_back(v[0]);
	ch.push_back(v[1]);

	for (i = 2; i < (int)v.size(); i++){
		c = v[i];
		b = ch.back();
		ch.pop_back();
		a = ch.back();

		while (((b - a) ^ (c - a)) < 0){
			b = a;
			ch.pop_back();
			a = ch.back();
		}

		ch.push_back(b);
		ch.push_back(c);
	}

	ch.pop_back();
}