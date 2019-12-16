/* O(Log(min(a, b))) - Calculates lcm(a, b) without overflowing. */
long long lcm(long long a, long long b) {
	return (a / __gcd(a, b)) * b;
}
