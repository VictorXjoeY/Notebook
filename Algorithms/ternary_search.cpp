#define eps 1e-9

double f(double x){
	// Define this function.
}

/* O(Log(R - L)). */
double maximum(double l, double r){
	while (r - l > eps){
		double m1 = l + (r - l) / 3.0;
		double m2 = l + 2.0 * (r - l) / 3.0;

		if (f(m1) < f(m2)){
			l = m1;
		}
		else{
			r = m2;
		}
	}

	return (l + r) / 2.0;
}

/* O(Log(R - L)). */
double minimum(double l, double r){
	while (r - l > eps){
		double m1 = l + (r - l) / 3.0;
		double m2 = l + 2.0 * (r - l) / 3.0;

		if (f(m1) < f(m2)){
			r = m2;
		}
		else{
			l = m1;
		}
	}

	return (l + r) / 2.0;
}

int f(int x){
	// Define this function.
}

/* O(Log(R - L)) - Must be strictly increasing or strictly decreasing where it is not Maximum. */
int maximum(int l, int r){
	while (l < r){
		int m = (l + r) / 2;

		if (f(m) <= f(m + 1)){
			l = m + 1;
		}
		else{
			r = m;
		}
	}

	return l;
}

/* O(Log(R - L)) - Must be strictly increasing or strictly decreasing where it is not Minimum. */
int minimum(int l, int r){
	while (l < r){
		int m = (l + r) / 2;

		if (f(m) <= f(m + 1)){
			r = m;
		}
		else{
			l = m + 1;
		}
	}

	return l;
}