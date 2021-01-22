template <class T>
class Point2D;

template <class T>
struct Point3D {
    T x, y, z;

    /* O(1) - Scalar sum. */
    Point3D<T> operator+(const T &c) const {
        return {this->x + c, this->y + c, this->z + c};
    }

    /* O(1) - Scalar subtraction. */
    Point3D<T> operator-(const T &c) const {
        return {this->x - c, this->y - c, this->z - c};
    }

    /* O(1) - Scalar multiplication. */
    Point3D<T> operator*(const T &c) const {
        return {this->x * c, this->y * c, this->z * c};
    }

    /* O(1) - Scalar division. */
    Point3D<T> operator/(const T &c) const {
        return {this->x / c, this->y / c, this->z / c};
    }

    /* O(1) - Negative vector. */
    Point3D<T> operator-() const {
        return {-this->x, -this->y, -this->z};
    }

    /* O(1) - Vector sum. */
    Point3D<T> operator+(const Point3D<T> &b) const {
        return {this->x + b.x, this->y + b.y, this->z + b.z};
    }

    /* O(1) - Vector subtraction. */
    Point3D<T> operator-(const Point3D<T> &b) const {
        return {this->x - b.x, this->y - b.y, this->z - b.z};
    }

    /* O(1) - Dot product. */
    T operator*(const Point3D<T> &b) const {
        return (this->x * b.x) + (this->y * b.y) + (this->z * b.z);
    }

    /* O(1) - Cross product. */
    Point3D<T> operator^(const Point3D<T> &b) const {
        return {(this->y * b.z) - (this->z * b.y), (this->z * b.x) - (this->x * b.z), (this->x * b.y) - (this->y * b.x)};
    }

    /* O(1) - Squared norm. */
    T operator!() const {
        return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
    }

    /* O(1) - Lesser than. */
    bool operator<(const Point3D<T> &b) const {
        if (this->x == b.x) {
            if (this->y == b.y) {
                return this->z < b.z;
            }

            return this->y < b.y;
        }

        return this->x < b.x;
    }

    /* O(1) - Greater than. */
    bool operator>(const Point3D<T> &b) const {
        return b < *this;
    }

    /* O(1) - Equal. */
    bool operator==(const Point3D<T> &b) const {
        return !(*this < b) and !(*this > b);
    }

    /* O(1) - Different. */
    bool operator!=(const Point3D<T> &b) const {
        return !(*this == b);
    }

    /* O(1). */
    template <class U>
    operator Point3D<U>() const {
        return {static_cast<U>(this->x), static_cast<U>(this->y), static_cast<U>(this->z)};
    }

    /* O(1). */
    template <class U>
    operator Point2D<U>() const {
        return {static_cast<U>(this->x) / static_cast<U>(this->z), static_cast<U>(this->y) / static_cast<U>(this->z)};
    }
};

/* O(1) - String conversion. */
template <class T>
string to_string(const Point3D<T> &p) {
    return "(" + to_string(p.x) + ", " + to_string(p.y) + +", " + to_string(p.z) + ")";
}

template <class T>
struct Point2D {
    T x, y;

    /* O(1) - Scalar sum. */
    Point2D<T> operator+(const T &c) const {
        return {this->x + c, this->y + c};
    }

    /* O(1) - Scalar subtraction. */
    Point2D<T> operator-(const T &c) const {
        return {this->x - c, this->y - c};
    }

    /* O(1) - Scalar multiplication. */
    Point2D<T> operator*(const T &c) const {
        return {this->x * c, this->y * c};
    }

    /* O(1) - Scalar division. */
    Point2D<T> operator/(const T &c) const {
        return {this->x / c, this->y / c};
    }

    /* O(1) - Negative vector. */
    Point2D<T> operator-() const {
        return {-this->x, -this->y};
    }

    /* O(1) - Vector sum. */
    Point2D<T> operator+(const Point2D<T> &b) const {
        return {this->x + b.x, this->y + b.y};
    }

    /* O(1) - Vector subtraction. */
    Point2D<T> operator-(const Point2D<T> &b) const {
        return {this->x - b.x, this->y - b.y};
    }

    /* O(1) - Dot product. */
    T operator*(const Point2D<T> &b) const {
        return (this->x * b.x) + (this->y * b.y);
    }

    /* O(1) - Cross product. */
    T operator^(const Point2D<T> &b) const {
        return (this->x * b.y) - (this->y * b.x);
    }

    /* O(1) - Squared norm. */
    T operator!() const {
        return (this->x * this->x) + (this->y * this->y);
    }

    /* O(1) - Lesser than. */
    bool operator<(const Point2D<T> &b) const {
        if (this->x == b.x) {
            return this->y < b.y;
        }

        return this->x < b.x;
    }

    /* O(1) - Greater than. */
    bool operator>(const Point2D<T> &b) const {
        return b < *this;
    }

    /* O(1) - Equal. */
    bool operator==(const Point2D<T> &b) const {
        return !(*this < b) and !(*this > b);
    }

    /* O(1) - Different. */
    bool operator!=(const Point2D<T> &b) const {
        return !(*this == b);
    }

    /* O(1). */
    template <class U>
    operator Point2D<U>() const {
        return {static_cast<U>(this->x), static_cast<U>(this->y)};
    }

    /* O(1). */
    template <class U>
    operator Point3D<U>() const {
        return {static_cast<U>(this->x), static_cast<U>(this->y), static_cast<U>(1)};
    }
};

/* O(1) - String conversion. */
template <class T>
string to_string(const Point2D<T> &p) {
    return "(" + to_string(p.x) + ", " + to_string(p.y) + ")";
}