class Point:
	# O(1) - Constructor.
	def __init__(self, x, y):
		self.x, self.y = x, y

	# O(1) - Vector subtraction.
	def __sub__(self, p):
		return Point(self.x - p.x, self.y - p.y)

	# O(1) - Dot product.
	def __mul__(self, p):
		return self.x * p.x + self.y * p.y

	# O(1) - Cross product.
	def __xor__(self, p):
		return self.x * p.y - self.y * p.x

	# O(1) - Equal.
	def __eq__(self, p):
		return self.x == p.x and self.y == p.y

# O(1) - Returns true if the point Q is inside the line defined by AB.
# Expects a non-degenerate line AB.
def point_inside_line(q, a, b):
	return (b - a) ^ (q - a) == 0

# O(1) - Returns -1 is Q is inside the segment AB, 0 if on a vertex and 1 if outside of the segment.
def point_inside_segment(q, a, b):
	# On a vertex.
	if q == a or q == b:
		return 0

	# Degenerate case.
	if a == b:
		return 1

	# General case.
	return -1 if point_inside_line(q, a, b) and (b - a) * (q - a) > 0 and (a - b) * (q - b) > 0 else 1
