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

		b >>= 1ll; // Next bit.
		a = (a * a) % m; // Next power of a.
	}

	return ans;
}