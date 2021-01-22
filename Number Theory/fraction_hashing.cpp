/* The time complexity of the division and construction can be exchanged by the time
complexity of the == comparison operator by storing both p and q modulo m instead of
just storing x = p * q^(-1) modulo m. */
constexpr long long mod[2] = {1000000007, 1000000009}; // Every individual fraction has to have a numerator and a denominator lesser than these mods.

/* O(Log(B)). */
long long fast_exp(long long a, long long b, long long m) {
    long long ans = 1; // Base case.

    // In case a >= m.
    a %= m;

    // Decomposing b in binary. Multiplying the answer by a^1, a^2, a^4, a^8, ...
    while (b > 0) {
        // If current bit is set.
        if (b & 1ll) {
            ans = (ans * a) % m;
        }

        b >>= 1ll;       // Next bit.
        a = (a * a) % m; // Next power of a.
    }

    return ans;
}

struct Fraction {
    long long x[2]; // Stores x = p * q^(-1) (mod m) with x >= 0

    /* O(Log(M)). */
    Fraction(long long p = 0, long long q = 1) {
        for (int k = 0; k < 2; k++) {
            x[k] = ((p * fast_exp(q, mod[k] - 2, mod[k])) % mod[k] + mod[k]) % mod[k];
        }
    }

    /* O(1). */
    Fraction operator-() const {
        Fraction f;

        for (int k = 0; k < 2; k++) {
            f.x[k] = (-x[k] + mod[k]) % mod[k];
        }

        return f;
    }
};

/* O(1). */
Fraction operator+(const Fraction &lhs, const Fraction &rhs) {
    Fraction f;

    for (int k = 0; k < 2; k++) {
        f.x[k] = (lhs.x[k] + rhs.x[k]) % mod[k];
    }

    return f;
}

/* O(1). */
Fraction operator-(const Fraction &lhs, const Fraction &rhs) {
    Fraction f;

    for (int k = 0; k < 2; k++) {
        f.x[k] = ((lhs.x[k] - rhs.x[k]) % mod[k] + mod[k]) % mod[k];
    }

    return f;
}

/* O(1). */
Fraction operator*(const Fraction &lhs, const Fraction &rhs) {
    Fraction f;

    for (int k = 0; k < 2; k++) {
        f.x[k] = (lhs.x[k] * rhs.x[k]) % mod[k];
    }

    return f;
}

/* O(Log(M)). */
Fraction operator/(const Fraction &lhs, const Fraction &rhs) {
    Fraction f;

    for (int k = 0; k < 2; k++) {
        f.x[k] = (lhs.x[k] * fast_exp(rhs.x[k], mod[k] - 2, mod[k])) % mod[k];
    }

    return f;
}

/* O(1) - Checks if two fraction are equal based on their hash values. */
bool operator==(const Fraction &lhs, const Fraction &rhs) {
    for (int k = 0; k < 2; k++) {
        if (lhs.x[k] != rhs.x[k]) {
            return false;
        }
    }

    return true;
}

/* O(1) - Checks if two fraction are different based on their hash values. */
bool operator!=(const Fraction &lhs, const Fraction &rhs) {
    return !(lhs == rhs);
}