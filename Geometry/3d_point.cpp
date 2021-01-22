template <class T>
struct Point {
    T x, y, z;

    /* O(1) - Scalar sum. */
    Point<T> operator+(const T &c) const {
        return {this->x + c, this->y + c, this->z + c};
    }

    /* O(1) - Scalar subtraction. */
    Point<T> operator-(const T &c) const {
        return {this->x - c, this->y - c, this->z - c};
    }

    /* O(1) - Scalar multiplication. */
    Point<T> operator*(const T &c) const {
        return {this->x * c, this->y * c, this->z * c};
    }

    /* O(1) - Scalar division. */
    Point<T> operator/(const T &c) const {
        return {this->x / c, this->y / c, this->z / c};
    }

    /* O(1) - Negative vector. */
    Point<T> operator-() const {
        return {-this->x, -this->y, -this->z};
    }

    /* O(1) - Vector sum. */
    Point<T> operator+(const Point<T> &b) const {
        return {this->x + b.x, this->y + b.y, this->z + b.z};
    }

    /* O(1) - Vector subtraction. */
    Point<T> operator-(const Point<T> &b) const {
        return {this->x - b.x, this->y - b.y, this->z - b.z};
    }

    /* O(1) - Dot product. */
    T operator*(const Point<T> &b) const {
        return (this->x * b.x) + (this->y * b.y) + (this->z * b.z);
    }

    /* O(1) - Cross product. */
    Point<T> operator^(const Point<T> &b) const {
        return {(this->y * b.z) - (this->z * b.y), (this->z * b.x) - (this->x * b.z), (this->x * b.y) - (this->y * b.x)};
    }

    /* O(1) - Squared norm. */
    T operator!() const {
        return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
    }

    /* O(1) - Lesser than. */
    bool operator<(const Point<T> &b) const {
        if (this->x == b.x) {
            if (this->y == b.y) {
                return this->z < b.z;
            }

            return this->y < b.y;
        }

        return this->x < b.x;
    }

    /* O(1) - Greater than. */
    bool operator>(const Point<T> &b) const {
        return b < *this;
    }

    /* O(1) - Equal. */
    bool operator==(const Point<T> &b) const {
        return !(*this < b) and !(*this > b);
    }

    /* O(1) - Different. */
    bool operator!=(const Point<T> &b) const {
        return !(*this == b);
    }
};

/* O(1) - String conversion. */
template <class T>
string to_string(const Point<T> &p) {
    return "(" + to_string(p.x) + ", " + to_string(p.y) + +", " + to_string(p.z) + ")";
}