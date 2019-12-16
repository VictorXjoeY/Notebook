# O(Log(min(a, b))) - Extended Euclidean Algorithm.
# Returns a solution to a * x + b * y = gcd(a, b).
# Returns |x| <= |a / gcd(a, b)|, |y| <= |b / gcd(a, b)| and gcd(a, b).
def extended_gcd(a, b):
	if a == 0:
		return (b, 0, 1)

	gcd, x, y = extended_gcd(b % a, a)

	return (gcd, y - (b // a) * x, x)
