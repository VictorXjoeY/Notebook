long long ceil(long long, long long);

/* O(1) - Integer division num / den that behaves like Python so that you can properly deal with inequations like x >= a / b. */
long long floor(long long num, long long den){
	if ((num >= 0 and den >= 0) or (num < 0 and den < 0)){
		return abs(num) / abs(den);
	}

	return -ceil(abs(num), abs(den));
}

/* O(1). */
long long ceil(long long num, long long den){
	return floor(num + den - 1, den);
}

/* O(Log(max(a, b))). */
/* a * x + b * y = gcd(a, b) */
long long extended_gcd(long long a, long long b, long long &x, long long &y){
	long long x1, y1, gcd;

	if (a == 0){
		x = 0;
		y = 1;
		return b;
	}
 
	gcd = extended_gcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
 
	return gcd;
}

/* O(Log(max(a, b))).
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
If a and/or b are 0, treat those cases separately. */
long long diophantine(long long a, long long b, long long c, long long &x1, long long &y1){
	long long gcd, k;

	// Obtaining a * x1 + b * y1 = gcd(a, b)
	gcd = extended_gcd(a, b, x1, y1);

	// No solution
	if (c % gcd != 0){
		return 0;
	}

	// Multiplying the above equation by k = c / gcd to obtain a * x1 + b * y1 = c
	x1 *= c / gcd;
	y1 *= c / gcd;

	// Simplifying the solution so that x1 is minimum and positive. Use positive values for a and b for this to work as intended!
	k = ceil(-x1 * gcd, b);
	x1 += k * (b / gcd);
	y1 -= k * (a / gcd);

	return gcd;
}