constexpr int N = 1000000;

bool prime[N + 1];

/* O(N * Log(Log(N))). */
vector<int> sieve(int n) {
    vector<int> p;

    // Initializing.
    memset(prime, true, sizeof(prime));
    prime[0] = prime[1] = false;

    // For every number i from 2 to N.
    for (int i = 2; i <= n; i++) {
        // If current number is prime.
        if (prime[i]) {
            p.push_back(i);

            // Marking its multiples as not prime.
            for (int j = i * i; j <= n; j += i) {
                prime[j] = false;
            }
        }
    }

    return p;
}