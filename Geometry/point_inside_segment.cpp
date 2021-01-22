template <class T>
struct Point {
    T x, y;

    /* O(1) - Vector subtraction. */
    Point<T> operator-(const Point<T> &b) const {
        return {this->x - b.x, this->y - b.y};
    }

    /* O(1) - Dot product. */
    T operator*(const Point<T> &b) const {
        return (this->x * b.x) + (this->y * b.y);
    }

    /* O(1) - Cross product. */
    T operator^(const Point<T> &b) const {
        return (this->x * b.y) - (this->y * b.x);
    }

    /* O(1) - Equal. */
    bool operator==(const Point &b) const {
        return this->x == b.x and this->y == b.y;
    }
};

/* O(1) - Returns true if the point Q is inside the line defined by AB.
   Expects a non-degenerate line AB. */
template <class T>
bool point_inside_line(const Point<T> &q, const Point<T> &a, const Point<T> &b) {
    return ((b - a) ^ (q - a)) == static_cast<T>(0);
}

/* O(1) - Returns -1 if Q is inside the segment AB, 0 if on a vertex and 1 if outside of the segment. */
template <class T>
int point_inside_segment(const Point<T> &q, const Point<T> &a, const Point<T> &b) {
    // On a vertex.
    if (q == a or q == b) {
        return 0;
    }

    // Degenerate case.
    if (a == b) {
        return 1;
    }

    // General case.
    return point_inside_line(q, a, b) and ((b - a) * (q - a)) > static_cast<T>(0) and ((a - b) * (q - b)) > static_cast<T>(0) ? -1 : 1;
}