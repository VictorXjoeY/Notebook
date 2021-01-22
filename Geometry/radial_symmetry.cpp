template <class T>
struct Point {
    T x, y;

    /* O(1) - Vector sum. */
    Point<T> operator+(const Point<T> &b) const {
        return {this->x + b.x, this->y + b.y};
    }

    /* O(1) - Equal. */
    bool operator==(const Point<T> &b) const {
        return this->x == b.x and this->y == b.y;
    }

    /* O(1) - Different. */
    bool operator!=(const Point<T> &b) const {
        return !(*this == b);
    }
};

/* O(N) - Returns true if the polygon has radial symmetry and false otherwise. */
template <class T>
bool radial_symmetry(const vector<Point<T>> &p) {
    if (p.size() % 2 != 0) {
        return false;
    }

    for (int i = 1; i < p.size() / 2; i++) {
        if (p[i] + p[i + p.size() / 2] != p[0] + p[p.size() / 2]) {
            return false;
        }
    }

    return true;
}