template <class T>
struct Point {
    T x, y;

    /* O(1) - Vector subtraction. */
    Point<T> operator-(const Point<T> &b) const {
        return {this->x - b.x, this->y - b.y};
    }

    /* O(1) - Cross product. */
    T operator^(const Point<T> &b) const {
        return (this->x * b.y) - (this->y * b.x);
    }

    /* O(1) - Compare function. */
    bool operator<(const Point<T> &b) const {
        if (this->x == b.x) {
            return this->y < b.y;
        }

        return this->x < b.x;
    }

    /* O(1) - Compare function. */
    bool operator==(const Point<T> &b) const {
        return this->x == b.x and this->y == b.y;
    }
};

/* O(N * Log(N)) - Sorts the points in an almost convex polygon in counter-clockwise order. */
template <class T>
void sort_convex_polygon(vector<Point<T>> &p) {
    int i;

    // Retrieving a pivot point.
    Point<T> pivot = *min_element(p.begin(), p.end());

    /* O(1) - Compares points A and B using their angle relative to the Pivot. */
    function<bool(const Point<T>, const Point<T>)> comp = [&pivot](const Point<T> &a, const Point<T> &b) {
        // Same angle. Closest point first.
        if (((a - pivot) ^ (b - pivot)) == static_cast<T>(0)) {
            return a < b;
        }

        // True if PA -> PB is a left turn.
        return ((a - pivot) ^ (b - pivot)) > static_cast<T>(0);
    };

    // Sorting according to angles relative to the pivot.
    sort(p.begin(), p.end(), comp);

    // Reversing last collinear part.
    for (i = (int)p.size() - 2; i >= 1; i--) {
        if (((p.back() - pivot) ^ (p[i] - pivot)) != static_cast<T>(0)) {
            break;
        }
    }

    reverse(p.begin() + i + 1, p.end());
}

/* O(N * Log(N)) - Returns the Convex Hull of a set of points. Expects at least one point. */
template <class T>
vector<Point<T>> graham_scan(vector<Point<T>> p) {
    vector<Point<T>> ch; // "Stack".
    Point<T> a, b, c;

    // Sorting and removing repeated points.
    sort_convex_polygon(p);
    p.resize(unique(p.begin(), p.end()) - p.begin());

    // Convex Hull of only one point.
    if (p.size() == 1) {
        ch.push_back(p[0]);
        return ch;
    }

    // Convex Hull of only collinear points.
    if (((p[1] - p[0]) ^ (p.back() - p[0])) == static_cast<T>(0)) {
        ch.push_back(p[0]);
        ch.push_back(p[1]);
        return ch;
    }

    // Pushing an extra Pivot as a sentinel.
    p.push_back(p[0]);

    // Pushing first two points.
    ch.push_back(p[0]); // Pivot.
    ch.push_back(p[1]);

    // Appending points to the Convex Hull one by one.
    for (int i = 2; i < p.size(); i++) {
        c = p[i];

        // There are always at least 2 points in the stack at this point.
        do {
            // Retrieving the top 2 from stack (A and B).
            b = ch.back();
            ch.pop_back();
            a = ch.back();
            ch.pop_back();

            // If it is a left turn, the three points belong to the current Convex Hull.
            if (((b - a) ^ (c - a)) > static_cast<T>(0)) {
                // Pushing back A and B.
                ch.push_back(a);
                ch.push_back(b);
                break;
            }

            // Not a left turn. Removing B by only pushing back A.
            ch.push_back(a);
        } while (ch.size() >= 2);

        // Appending C.
        ch.push_back(c);
    }

    // Removing the Pivot initially pushed as a sentinel.
    ch.pop_back();

    return ch;
}