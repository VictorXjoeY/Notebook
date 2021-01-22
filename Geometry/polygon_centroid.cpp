template <class T>
struct Point {
    T x, y;

    /* O(1) - Scalar division. */
    Point<T> operator/(const T &c) const {
        return {this->x / c, this->y / c};
    }

    /* O(1) - Cross product. */
    T operator^(const Point<T> &b) const {
        return (this->x * b.y) - (this->y * b.x);
    }
};

/* O(N) - Computes twice the signed area of a convex or non-convex polygon, being it simple or self-intersecting.
   Expects a polygon either in clockwise or in counter-clockwise order. */
template <class T>
T shoelace(const vector<Point<T>> &p) {
    T ans = static_cast<T>(0);

    for (int i = 0; i < p.size(); i++) {
        ans = ans + (p[i] ^ p[(i + 1) % p.size()]);
    }

    return ans;
}

/* O(N) - Computes the center of mass of a simple polygon.
   Caution with overflowing Fractions because the numerator is of the order of x^3 and y^3.
   Expects a polygon either in clockwise or in counter-clockwise order. */
template <class T>
Point<T> centroid(const vector<Point<T>> &p) {
    Point<T> c = {static_cast<T>(0), static_cast<T>(0)};

    for (int i = 0; i < p.size(); i++) {
        c.x = c.x + (p[i].x + p[(i + 1) % p.size()].x) * (p[i] ^ p[(i + 1) % p.size()]);
        c.y = c.y + (p[i].y + p[(i + 1) % p.size()].y) * (p[i] ^ p[(i + 1) % p.size()]);
    }

    return c / (static_cast<T>(3) * shoelace(p));
}