#define eps 1e-9

double f(double x){
	// Define this function.
}

/* O(Log(N)). */
void ternary_search_double(){
	double l, r, m1, m2;

	// Maximum.
	while (r - l > eps){
		m1 = l + (r - l) / 3.0;
		m2 = l + 2.0 * (r - l) / 3.0;

		if (f(m1) < f(m2)){
			l = m1;
		}
		else{
			r = m2;
		}
	}

	// Minimum.
	while (r - l > eps){
		m1 = l + (r - l) / 3.0;
		m2 = l + 2.0 * (r - l) / 3.0;

		if (f(m1) < f(m2)){
			r = m2;
		}
		else{
			l = m1;
		}
	}
}

int f(int x){
	// Define this function.
}

/* O(Log(N)) - Must be strictly increasing or strictly decreasing where it is not Maximum/Minimum. */
void ternary_search_int(){
	int l, r, m;

	// Maximum.
	while (l < r){
		m = (l + r) / 2;

		if (f(m) <= f(m + 1)){
			l = m + 1;
		}
		else{
			r = m;
		}
	}

	// Minimum.
	while (l < r){
		m = (l + r) / 2;

		if (f(m) <= f(m + 1)){
			r = m;
		}
		else{
			l = m + 1;
		}
	}
}