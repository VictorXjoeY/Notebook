class Point:
	# O(1) - Constructor.
	def __init__(self, x, y, z):
		self.x, self.y, self.z = x, y, z

	# O(1) - Vector sum.
	def __add__(self, p):
		return Point(self.x + p.x, self.y + p.y, self.z + p.z)

	# O(1) - Negative vector.
	def __neg__(self):
		return Point(-self.x, -self.y, -self.z)

	# O(1) - Vector subtraction.
	def __sub__(self, p):
		return Point(self.x - p.x, self.y - p.y, self.z - p.z)

	# O(1) - Dot product.
	def __mul__(self, p):
		return self.x * p.x + self.y * p.y + self.z * p.z

	# O(1) - Cross product.
	def __xor__(self, p):
		return Point(self.y * p.z - self.z * p.y, self.z * p.x - self.x * p.z, self.x * p.y - self.y * p.x)

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