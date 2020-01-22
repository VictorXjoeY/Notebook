class Point3D:
	# O(1) - Constructor.
	def __init__(self, x, y, z):
		self.x, self.y, self.z = x, y, z

	# O(1) - Vector sum.
	def __add__(self, p):
		return Point3D(self.x + p.x, self.y + p.y, self.z + p.z)

	# O(1) - Negative vector.
	def __neg__(self):
		return Point3D(-self.x, -self.y, -self.z)

	# O(1) - Vector subtraction.
	def __sub__(self, p):
		return Point3D(self.x - p.x, self.y - p.y, self.z - p.z)

	# O(1) - Dot product.
	def __mul__(self, p):
		return self.x * p.x + self.y * p.y + self.z * p.z

	# O(1) - Cross product.
	def __xor__(self, p):
		return Point3D(self.y * p.z - self.z * p.y, self.z * p.x - self.x * p.z, self.x * p.y - self.y * p.x)

	# O(1) - Lesser than.
	def __lt__(self, p):
		if self.x == p.x:
			if self.y == p.y:
				return self.z < p.z

			return self.y < p.y

		return self.x < p.x

	# O(1) - Greater than.
	def __gt__(self, p):
		return p < self

	# O(1) - Equal.
	def __eq__(self, p):
		return self.x == p.x and self.y == p.y and self.z == p.z

	# O(1) - Different.
	def __ne__(self, p):
		return not self == p

	# O(1) - String conversion.
	def __str__(self):
		return "(%s, %s, %s)" % (str(self.x), str(self.y), str(self.z))

	# O(1) - String conversion for printing arrays.
	def __repr__(self):
		return str(self)

class Point2D:
	# O(1) - Constructor.
	def __init__(self, x, y):
		self.x, self.y = x, y

	# O(1) - Vector sum.
	def __add__(self, p):
		return Point2D(self.x + p.x, self.y + p.y)

	# O(1) - Negative vector.
	def __neg__(self):
		return Point2D(-self.x, -self.y)

	# O(1) - Vector subtraction.
	def __sub__(self, p):
		return Point2D(self.x - p.x, self.y - p.y)

	# O(1) - Dot product.
	def __mul__(self, p):
		return self.x * p.x + self.y * p.y

	# O(1) - Cross product.
	def __xor__(self, p):
		return self.x * p.y - self.y * p.x

	# O(1) - Lesser than.
	def __lt__(self, p):
		if self.x == p.x:
			return self.y < p.y

		return self.x < p.x

	# O(1) - Greater than.
	def __gt__(self, p):
		return p < self

	# O(1) - Equal.
	def __eq__(self, p):
		return self.x == p.x and self.y == p.y

	# O(1) - Different.
	def __ne__(self, p):
		return not self == p

	# O(1) - String conversion.
	def __str__(self):
		return "(%s, %s)" % (str(self.x), str(self.y))

	# O(1) - String conversion for printing arrays.
	def __repr__(self):
		return str(self)

# O(1) - Converts between 2D points and 3D points.
def convert(p):
	if isinstance(p, Point2D):
		return Point3D(p.x, p.y, 1)

	return Point2D(p.x / p.z, p.y / p.z)

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


# O(1) - Returns 0 if the lines don't intersect. Returns 1 if the lines intersect at 1 point. Returns 2 if the lines are the same.
# Expects non-degenerate lines.
def line_line_intersects(a, b, c, d):
	assert(a != b and c != d)

	# Parallel lines.
	if (b - a) ^ (d - c) == 0:
		return 2 if point_inside_line(c, a, b) else 0

	# General case.
	return 1

# O(1) - Returns the point of intersection between a line defined by AB and a line defined by CD.
# You need to first guarantee that the lines have exactly 1 intersection point.
def line_line_intersection(a, b, c, d):
	assert(line_line_intersects(a, b, c, d) == 1)
	return convert((convert(a) ^ convert(b)) ^ (convert(c) ^ convert(d)))

# O(1) - Returns a vector with: 0 points if there's no intersection, 1 point if the segments intersect at 1 point or 2 points if the segments share a segment of points.
def segment_segment_intersection(a, b, c, d):
	# Degenerate case.
	if a == b:
		if point_inside_segment(a, c, d) <= 0:
			return [a]

		return []

	# Degenerate case.
	if c == d:
		if point_inside_segment(c, a, b) <= 0:
			return [c]

		return []

	# 1 line intersection.
	if line_line_intersects(a, b, c, d) == 0:
		return []

	if line_line_intersects(a, b, c, d) == 1:
		q = line_line_intersection(a, b, c, d)

		# If the intersection of the two lines is inside the two segments.
		if point_inside_segment(q, a, b) <= 0 and point_inside_segment(q, c, d) <= 0:
			return [q]

		return []

	# Both segments are in the same line.
	q = []

	if point_inside_segment(a, c, d) <= 0:
		q.append(a)

	if point_inside_segment(b, c, d) <= 0:
		q.append(b)

	if point_inside_segment(c, a, b) <= 0:
		q.append(c)

	if point_inside_segment(d, a, b) <= 0:
		q.append(d)

	# Retrieving sorted and unique points.
	q.sort()
	ans = []

	for p in q:
		if len(ans) == 0 or ans[-1] != p:
			ans.append(p)

	return ans
