long long ceil_div(long long, long long);

/* O(1) - Integer division num / den that behaves like Python so that you can properly deal with inequations like x >= a / b. */
long long floor_div(long long num, long long den) {
	if ((num >= 0 and den >= 0) or (num < 0 and den < 0)) {
		return abs(num) / abs(den);
	}

	return -ceil_div(abs(num), abs(den));
}

/* O(1). */
long long ceil_div(long long num, long long den) {
	return floor_div(num + den - 1, den);
}

bool check(int m) {
	// Define this function.
	return m > 0;
}

/* O(Log(R - L)). */
int last_false(int l, int r) {
	while (l < r) {
		int m = ceil_div(l + r, 2);

		if (check(m)) {
			r = m - 1;
		}
		else{
			l = m;
		}
	}

	return l;
}

/* O(Log(R - L)). */
int first_true(int l, int r) {
	while (l < r) {
		int m = floor_div(l + r, 2);

		if (check(m)) {
			r = m;
		}
		else{
			l = m + 1;
		}
	}

	return l;
}

/* O(Log(R - L)). */
int last_true(int l, int r) {
	while (l < r) {
		int m = ceil_div(l + r, 2);

		if (check(m)) {
			l = m;
		}
		else{
			r = m - 1;
		}
	}

	return l;
}

/* O(Log(R - L)). */
int first_false(int l, int r) {
	while (l < r) {
		int m = floor_div(l + r, 2);

		if (check(m)) {
			l = m + 1;
		}
		else{
			r = m;
		}
	}

	return l;
}

constexpr double eps = 1e-9;

bool check(double m) {
	// Define this function.
	return m > 0.0;
}

/* O(Log(R - L)). */
double last_false(double l, double r) {
	while (r - l > eps) {
		double m = (l + r) / 2.0;

		if (check(m)) {
			r = m;
		}
		else{
			l = m;
		}
	}

	return l;
}

/* O(Log(R - L)). */
double first_true(double l, double r) {
	while (r - l > eps) {
		double m = (l + r) / 2.0;

		if (check(m)) {
			r = m;
		}
		else{
			l = m;
		}
	}

	return r;
}

/* O(Log(R - L)). */
double last_true(double l, double r) {
	while (r - l > eps) {
		double m = (l + r) / 2.0;

		if (check(m)) {
			l = m;
		}
		else{
			r = m;
		}
	}

	return l;
}

/* O(Log(R - L)). */
double first_false(double l, double r) {
	while (r - l > eps) {
		double m = (l + r) / 2.0;

		if (check(m)) {
			l = m;
		}
		else{
			r = m;
		}
	}

	return r;
}