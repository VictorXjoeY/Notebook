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
	gcd, x, y = extended_gcd(a, b)

	# No solution
	if c % gcd != 0:
		return (0, 0, 0)

	# Multiplying the above equation by k = c / gcd to obtain a * x1 + b * y1 = c
	return (gcd, x * (c // gcd), y * (c // gcd))