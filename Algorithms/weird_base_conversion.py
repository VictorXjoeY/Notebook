# D - Secure but True - 2015 ACM Syrian Collegiate Programming Contest
# codeforces.com/gym/101086/problem/D

# O(N). Converts the list of digits l to a decimal.
def to_decimal(l, base, from_digit):
	power = 1
	ans = 0

	# From the less significative digit to the most significative digit.
	for i in range(len(l) - 1, -1, -1):
		ans += from_digit[l[i]] * power # Adding l[i]'s value.
		power *= base # Updating the power of base.
	
	return ans

# O(N). Converts the decimal n to a list of digits in a certain base.
def to_base(n, base):
	l = []
	
	# Extracting digits.
	while n > 0:
		l.append(n % base)
		n //= base

	# Reversing digits.
	return l[::-1]

# O(N). Converts the decimal n to a list of digits.
def from_decimal(n, base, to_digit):
	l = to_base(n, base)

	# From the less significative digit to the most significative digit.
	for i in range(len(l) - 1, 0, -1):
		if l[i] <= 0:
			# "Lending" 1 from the left digit.
			l[i] += base
			l[i - 1] -= 1

		# Converting the current value.
		l[i] = to_digit[l[i]]

	# Converting most significant digit.
	if l[0] > 0:
		l[0] = to_digit[l[0]]
		return l

	# If most significant digit doesn't exist.
	return l[1:]

def main():
	# Initializing base and conversion dictionaries.
	base = 11
	from_digit = {'A': 1, 'H': 2, 'I': 3, 'M': 4, 'O': 5, 'T': 6, 'U': 7, 'V': 8, 'W': 9, 'X': 10, 'Y': 11}
	to_digit = {1 : 'A', 2 : 'H', 3 : 'I', 4 : 'M', 5 : 'O', 6 : 'T', 7 : 'U', 8 : 'V', 9 : 'W', 10 : 'X', 11 : 'Y'}

	t = int(input())

	for i in range(t):
		# Reading input.
		line = input().split()
		k = int(line[0])
		s = line[1]

		# Obtaining answer.
		ans = from_decimal(to_decimal(s, base, from_digit) + k, base, to_digit)

		# Printing answer.
		print("".join(ans))
		
if __name__ == "__main__":
	main()