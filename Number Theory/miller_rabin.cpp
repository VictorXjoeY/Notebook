/* O(Log(B)). */
long long fast_exp(long long a, long long b, long long m){
	long long ans = 1; // Base case.

	// In case a >= m.
	a %= m;

	// Decomposing b in binary. Multiplying the answer by a^1, a^2, a^4, a^8, ...
	while (b > 0){
		// If current bit is set.
		if (b & 1ll){
			ans = (ans * a) % m;
		}

		b >>= 1ll; // Next bit.
		a = (a * a) % m; // Next power of a.
	}

	return ans;
}

/* O(Log(N)) - Returns true if n is probably prime and returns false if it composite for sure. */
bool is_probably_prime(long long n, long long a, long long d, int s){
	long long x = fast_exp(a, d, n);

	// a^d = 1 (mod n)
	if (x == 1){
		return true;
	}

	// a^(d * 2^r) = -1 (mod n), 0 <= r < s
	for (int r = 0; r < s; r++){
		if (x == n - 1){
			return true;
		}

		x = ((__int128)x * (__int128)x) % n;
	}

	return false;
}

/* O(12 * Log(N)) - Deterministic Miller Rabin for 64 bit integers. Returns true if n is prime and returns false otherwise. */
bool miller_rabin(long long n){
	long long a[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

	if (n <= 1){
		return false;
	}

	// O(Log(N) - Decomposing n - 1 = d * 2^s
	int s = 0;
	long long d = n - 1;

	while (d % 2 == 0){
		d /= 2;
		s++;
	}

	// For each prime base a[i].
	for (int i = 0; i < 12; i++){
		if (n == a[i]){
			return true;
		}

		if (!is_probably_prime(n, a[i], d, s)){
			return false;
		}
	}

	return true;
}