constexpr int N = 1000000;

int mp[N + 1]; // mp[i] stores the minimum prime number which divides i. i is prime if it's not 0 and mp[i] == i.
int phi[N + 1];

/* O(N). */
vector<int> linear_sieve(int n) {
    vector<int> p; // Stores prime numbers.
    phi[1] = 1;

    for (int i = 2; i <= n; i++) {
        if (!mp[i]) { // i is prime if we haven't found any smaller factors of it.
            phi[i] = i - 1;
            mp[i] = i;
            p.push_back(i);
        }

        // Since every number x can be written as x = i * mp[x] we can iterate over every prime mp[x] (prime[j]).
        for (int j = 0; j < p.size() and p[j] <= mp[i] and i * p[j] <= n; j++) {
            // phi[x] = phi[i * mp[x]] = phi[i] * mp[x] if mp[x] divides i or phi[i] * (mp[x] - 1) if mp[x] doesn't divide i.
            phi[i * p[j]] = phi[i] * (p[j] == mp[i] ? p[j] : p[j] - 1);
            mp[i * p[j]] = p[j];
        }
    }

    return p;
}