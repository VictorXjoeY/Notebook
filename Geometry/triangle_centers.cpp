template <class T>
class Point2D;

template <class T>
struct Point3D {
    T x, y, z;

    /* O(1) - Cross product. */
    Point3D<T> operator^(const Point3D<T> &b) const {
        return {(this->y * b.z) - (this->z * b.y), (this->z * b.x) - (this->x * b.z), (this->x * b.y) - (this->y * b.x)};
    }

    /* O(1). */
    template <class U>
    operator Point2D<U>() const {
        return {static_cast<U>(this->x) / static_cast<U>(this->z), static_cast<U>(this->y) / static_cast<U>(this->z)};
    }
};

template <class T>
struct Point2D {
    T x, y;

    /* O(1) - Scalar multiplication. */
    Point2D<T> operator*(const T &c) const {
        return {this->x * c, this->y * c};
    }

    /* O(1) - Scalar division. */
    Point2D<T> operator/(const T &c) const {
        return {this->x / c, this->y / c};
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

    /* O(1) - Equal. */
    bool operator==(const Point2D<T> &b) const {
        return this->x == b.x and this->y == b.y;
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

/* O(1) - Returns true if the point Q is inside the line defined by AB. */
template <class T>
bool point_inside_line(const Point2D<T> &q, const Point2D<T> &a, const Point2D<T> &b) {
    return ((b - a) ^ (q - a)) == static_cast<T>(0);
}

/* O(1) - Returns 0 if the lines don't intersect. Returns 1 if the lines intersect at 1 point. Returns 2 if the lines are the same.
   Expects non-degenerate lines. */
template <class T>
int line_line_intersects(const Point2D<T> &a, const Point2D<T> &b, const Point2D<T> &c, const Point2D<T> &d) {
    assert(a != b and c != d); // Can't have degenerate lines.

    // Parallel lines.
    if (((b - a) ^ (d - c)) == static_cast<T>(0)) {
        return point_inside_line(c, a, b) ? 2 : 0;
    }

    // General case.
    return 1;
}

/* O(1) - Returns the point of intersection between a line defined by AB and a line defined by CD.
   Expects non-degenerate lines that have exactly 1 intersection point.
   Caution with overflowing the Fractions because the numerator and the denominator of the intersection point will be of the order of x^4 and y^4. */
template <class T, class U>
Point2D<T> line_line_intersection(const Point2D<U> &a, const Point2D<U> &b, const Point2D<U> &c, const Point2D<U> &d) {
    assert(line_line_intersects(a, b, c, d) == 1); // Guarantees that it has exactly 1 intersection point.
    return static_cast<Point2D<T>>((static_cast<Point3D<U>>(a) ^ static_cast<Point3D<U>>(b)) ^ (static_cast<Point3D<U>>(c) ^ static_cast<Point3D<U>>(d)));
}

/* O(1) - Rotates vector p by 90 degrees. */
template <class T>
Point2D<T> rotate90(const Point2D<T> &p) {
    return {-p.y, p.x};
}

/* O(N) - Computes the Barycenter/Centroid of a triangle. */
template <class T, class U>
Point2D<T> centroid(const Point2D<U> &a, const Point2D<U> &b, const Point2D<U> &c) {
    assert(!point_inside_line(a, b, c)); // Can't have a degenerate triangle.
    return static_cast<Point2D<T>>(a + b + c) / static_cast<T>(3);
}

/* O(N) - Computes the center of the circle inscribed in the triangle.
   Expects a non-degenerate triangle. */
Point2D<double> incenter(const Point2D<double> &a, const Point2D<double> &b, const Point2D<double> &c) {
    assert(!point_inside_line(a, b, c)); // Can't have a degenerate triangle.

    double sa = sqrt(!(c - b));
    double sb = sqrt(!(a - c));
    double sc = sqrt(!(b - a));

    return ((a * sa) + (b * sb) + (c * sc)) / (sa + sb + sc);
}

/* O(N) - Computes the Orthocenter of the triangle.
   Expects a non-degenerate triangle. */
template <class T, class U>
Point2D<T> orthocenter(const Point2D<U> &a, const Point2D<U> &b, const Point2D<U> &c) {
    assert(!point_inside_line(a, b, c)); // Can't have a degenerate triangle.
    return line_line_intersection<T>(a, a + rotate90(c - b), b, b + rotate90(a - c));
}

/* O(N) - Computes the center of the circle around the triangle that touches its 3 vertices.
   Expects a non-degenerate triangle. */
template <class T, class U>
Point2D<T> circumcenter(const Point2D<U> &a, const Point2D<U> &b, const Point2D<U> &c) {
    assert(!point_inside_line(a, b, c)); // Can't have a degenerate triangle.

    Point2D<T> ab_m = static_cast<Point2D<T>>(a + b) / static_cast<T>(2);
    Point2D<T> ab_d = static_cast<Point2D<T>>(rotate90(b - a));
    Point2D<T> bc_m = static_cast<Point2D<T>>(b + c) / static_cast<T>(2);
    Point2D<T> bc_d = static_cast<Point2D<T>>(rotate90(c - b));

    return line_line_intersection<T>(ab_m, ab_m + ab_d, bc_m, bc_m + bc_d);
}

/* O(N) - Computes the center of the smallest circle that encloses the triangle.
   Expects a non-degenerate triangle. */
template <class T, class U>
Point2D<T> smallest_enclosing_circle(const Point2D<U> &a, const Point2D<U> &b, const Point2D<U> &c) {
    // Angle opposite to CA is >= 90 degrees.
    if (((b - a) * (c - b)) >= 0) {
        return static_cast<Point2D<T>>(c + a) / static_cast<T>(2);
    }

    // Angle opposite to AB is >= 90 degrees.
    if (((c - b) * (a - c)) >= 0) {
        return static_cast<Point2D<T>>(a + b) / static_cast<T>(2);
    }

    // Angle opposite to BC is >= 90 degrees.
    if (((a - c) * (b - a)) >= 0) {
        return static_cast<Point2D<T>>(b + c) / static_cast<T>(2);
    }

    return circumcenter<T>(a, b, c);
}