/* O(sqrt(N)). */
long long euler_phi(long long n) {
    long long ans = n;

    // For every prime p up to sqrt(n).
    for (long long p = 2; p * p <= n; p++) {
        // If prime p divides n.
        if (n % p == 0) {
            ans /= p;
            ans *= (p - 1);

            // Removing every p factor.
            while (n % p == 0) {
                n /= p;
            }
        }
    }

    // If n is not 1 by now, then it is a prime factor.
    if (n > 1) {
        ans /= n;
        ans *= (n - 1);
    }

    return ans;
}