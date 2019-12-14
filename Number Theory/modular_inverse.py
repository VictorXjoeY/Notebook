# O(Log(min(a, b))).
# a * x + b * y = gcd(a, b)
def extended_gcd(a, b):
	if a == 0:
		return (b, 0, 1)

	gcd, x, y = extended_gcd(b % a, a)

	return (gcd, y - (b // a) * x, x)

# O(Log(M)) - Returns the modular multiplicative inverse of a mod m, if it exists.
# Returns x that satisfies a * x = 1 (mod m) if a and m are coprime. Returns 0 otherwise.
def modular_inverse(a, m):
	g, x, y = extended_gcd((a % m + m) % m, m)

	if g != 1:
		return 0

	return (x % m + m) % m