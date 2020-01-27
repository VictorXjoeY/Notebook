/* O(Log(min(a, b))) - Extended Euclidean Algorithm.
   Returns a solution to a * x + b * y = gcd(a, b).
   Returns |x| <= |a / gcd(a, b)|, |y| <= |b / gcd(a, b)| and gcd(a, b). */
tuple<long long, long long, long long> extended_gcd(long long a, long long b) {
	long long x, y, gcd;

	if (a == 0) {
		return {b, 0, 1};
	}

	tie(gcd, x, y) = extended_gcd(b % a, a);

	return {gcd, y - (b / a) * x, x}; 
}

/* O(Log(min(a, b))).
a * x + b * y = c
	x = x1 + k * (b / gcd(a, b))
	y = y1 - k * (a / gcd(a, b))

a * x - b * y = c ---> a * x + b * (-y) = c
	x = x1 + k * (b / gcd(a, b))
	-y = y1 - k * (a / gcd(a, b)) ---> y = -y1 + k * (a / gcd(a, b))

-a * x + b * y = c ---> a * (-x) + b * y = c
	-x = x1 + k * (b / gcd(a, b)) ---> x = -x1 - k * (b / gcd(a, b))
	y = y1 - k * (a / gcd(a, b))

-a * x - b * y = c ---> a * (-x) + b * (-y) = c
	-x = x1 + k * (b / gcd(a, b)) ---> x = -x1 - k * (b / gcd(a, b))
	-y = y1 - k * (a / gcd(a, b)) ---> y = -y1 + k * (a / gcd(a, b))

Use positive values for a and b for this function.
Has infinite solutions if and only if gcd(a, b) divides c.
If a and/or b are 0, treat those cases separately.
Returns |x1| <= |(a * c) / gcd^2(a, b)|, |y1| <= |(b * c) / gcd^2(a, b)| and gcd(a, b) if there are solutions. */
tuple<long long, long long, long long> diophantine(long long a, long long b, long long c) {
	long long gcd, x, y;

	// Obtaining a * x1 + b * y1 = gcd(a, b)
	tie(gcd, x, y) = extended_gcd(a, b);

	// No solution
	if (c % gcd != 0) {
		return {0, 0, 0};
	}

	// Multiplying the above equation by k = c / gcd to obtain a * x1 + b * y1 = c
	return {gcd, x * (c / gcd), y * (c / gcd)};
}