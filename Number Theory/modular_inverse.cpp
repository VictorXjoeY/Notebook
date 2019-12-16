/* O(Log(min(a, b))) - Extended Euclidean Algorithm.
   Returns a solution to a * x + b * y = gcd(a, b).
   Returns |x| <= |a / gcd(a, b)|, |y| <= |b / gcd(a, b)| and gcd(a, b). */
long long extended_gcd(long long a, long long b, long long &x, long long &y) {
	long long x1, y1, gcd;

	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}
 
	gcd = extended_gcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
 
	return gcd;
}

/* O(Log(M)) - Returns the modular multiplicative inverse of a mod m, if it exists.
Returns x that satisfies a * x = 1 (mod m) if a and m are coprime. Returns 0 otherwise. */
long long modular_inverse(long long a, long long m) {
	long long x, y;

	if (extended_gcd((a % m + m) % m, m, x, y) != 1) {
		return 0;
	}

	return (x % m + m) % m;
}
