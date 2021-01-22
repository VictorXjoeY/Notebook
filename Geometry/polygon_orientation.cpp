template <class T>
struct Point {
    T x, y;

    /* O(1) - Cross product. */
    T operator^(const Point &b) const {
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

/* O(N) - Returns true if the points of the given simple polygon are in clockwise order. */
template <class T>
bool is_clockwise(const vector<Point<T>> &p) {
    return shoelace(p) < static_cast<T>(0);
}