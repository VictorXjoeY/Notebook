#define eps 1e-9

bool check(double m){
	// Define this function.
}

/* O(Log(N)). */
void binary_search_double(){
	double l, r, m;

	// Last false or first true.
	while (r - l > eps){
		m = (l + r) / 2.0;

		if (check(m)){
			r = m;
		}
		else{
			l = m;
		}
	}

	// Last true or first false.
	while (r - l > eps){
		m = (l + r) / 2.0;

		if (check(m)){
			l = m;
		}
		else{
			r = m;
		}
	}
}

bool check(int m){
	// Define this function.
}

/* O(Log(N)). */
void binary_search_int(){
	int l, r, m;

	// Last false.
	while (l < r){
		m = (l + r + 1) / 2;

		if (check(m)){
			r = m - 1;
		}
		else{
			l = m;
		}
	}

	// First true.
	while (l < r){
		m = (l + r) / 2;

		if (check(m)){
			r = m;
		}
		else{
			l = m + 1;
		}
	}

	// Last true.
	while (l < r){
		m = (l + r + 1) / 2;

		if (check(m)){
			l = m;
		}
		else{
			r = m - 1;
		}
	}

	// First false.
	while (l < r){
		m = (l + r) / 2;

		if (check(m)){
			l = m + 1;
		}
		else{
			r = m;
		}
	}
}
