#define eps 1e-9

bool check(double m){
	// Define this function.
}

/* O(Log(R - L)). */
double last_false(double l, double r){
	while (r - l > eps){
		m = (l + r) / 2.0;

		if (check(m)){
			r = m;
		}
		else{
			l = m;
		}
	}

	return l;
}

/* O(Log(R - L)). */
double first_true(double l, double r){
	while (r - l > eps){
		m = (l + r) / 2.0;

		if (check(m)){
			r = m;
		}
		else{
			l = m;
		}
	}

	return r;
}

/* O(Log(R - L)). */
double last_true(double l, double r){
	while (r - l > eps){
		m = (l + r) / 2.0;

		if (check(m)){
			l = m;
		}
		else{
			r = m;
		}
	}

	return l;
}

/* O(Log(R - L)). */
double first_false(double l, double r){
	while (r - l > eps){
		m = (l + r) / 2.0;

		if (check(m)){
			l = m;
		}
		else{
			r = m;
		}
	}

	return r;
}


bool check(int m){
	// Define this function.
}

/* O(Log(R - L)). */
int last_false(int l, int r){
	while (l < r){
		int m = (l + r + 1) / 2;

		if (check(m)){
			r = m - 1;
		}
		else{
			l = m;
		}
	}

	return l;
}

/* O(Log(R - L)). */
int first_true(int l, int r){
	while (l < r){
		int m = (l + r) / 2;

		if (check(m)){
			r = m;
		}
		else{
			l = m + 1;
		}
	}

	return l;
}

/* O(Log(R - L)). */
int last_true(int l, int r){
	while (l < r){
		int m = (l + r + 1) / 2;

		if (check(m)){
			l = m;
		}
		else{
			r = m - 1;
		}
	}

	return l;
}

/* O(Log(R - L)). */
int first_false(int l, int r){
	while (l < r){
		int m = (l + r) / 2;

		if (check(m)){
			l = m + 1;
		}
		else{
			r = m;
		}
	}

	return l;
}
