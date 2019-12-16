# O(Log(N)) - Returns the greatest integer k such that k^2 <= n.
def integer_sqrt(n):
	l, r = 0, n

	while l < r:
		m = (l + r + 1) // 2

		if m * m <= n:
			l = m
		else:
			r = m - 1

	return l
