# O(1).
def ceil(num, den):
	return (num + den - 1) // den

# O(Log(min(a, b))) - Extended Euclidean Algorithm.
# Returns a solution to a * x + b * y = gcd(a, b).
# Returns |x| <= |a / gcd(a, b)|, |y| <= |b / gcd(a, b)| and gcd(a, b).
def extended_gcd(a, b):
	if a == 0:
		return (b, 0, 1)

	gcd, x, y = extended_gcd(b % a, a)

	return (gcd, y - (b // a) * x, x)

# O(Log(min(a, b))).
# a * x + b * y = c
# 	x = x1 + k * (b / gcd(a, b))
# 	y = y1 - k * (a / gcd(a, b))
# 
# a * x - b * y = c ---> a * x + b * (-y) = c
# 	x = x1 + k * (b / gcd(a, b))
# 	-y = y1 - k * (a / gcd(a, b)) ---> y = -y1 + k * (a / gcd(a, b))
# 
# -a * x + b * y = c ---> a * (-x) + b * y = c
# 	-x = x1 + k * (b / gcd(a, b)) ---> x = -x1 - k * (b / gcd(a, b))
# 	y = y1 - k * (a / gcd(a, b))
# 
# -a * x - b * y = c ---> a * (-x) + b * (-y) = c
# 	-x = x1 + k * (b / gcd(a, b)) ---> x = -x1 - k * (b / gcd(a, b))
# 	-y = y1 - k * (a / gcd(a, b)) ---> y = -y1 + k * (a / gcd(a, b))
# 
# Use positive values for a and b for this function.
# Has infinite solutions if and only if gcd(a, b) divides c.
# If a and/or b are 0, treat those cases separately.
def diophantine(a, b, c):
	# Obtaining a * x1 + b * y1 = gcd(a, b)
	gcd, x1, y1 = extended_gcd(a, b)

	# No solution
	if c % gcd != 0:
		return (0, 0, 0)

	# Multiplying the above equation by k = c / gcd to obtain a * x1 + b * y1 = c
	x1 *= c // gcd
	y1 *= c // gcd

	# Simplifying the solution so that x1 is minimum and non-negative. Use positive values for a and b for this to work as intended!
	k = ceil(-x1 * gcd, b)
	x1 += k * (b // gcd)
	y1 -= k * (a // gcd)

	return (gcd, x1, y1)
