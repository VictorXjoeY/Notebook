/* O(sqrt(N)). */
int mobius(long long n) {
    int ans = 0;

    // For every prime p up to sqrt(n).
    for (long long p = 2; p * p <= n; p++) {
        // If prime p divides n.
        if (n % p == 0) {
            // Not square-free.
            if (n % (p * p) == 0) {
                return 0;
            }

            ans++;
            n /= p;
        }
    }

    // If n is not 1 by now, then it is a prime factor.
    ans += (n > 1);

    return ans % 2 == 0 ? 1 : -1;
}