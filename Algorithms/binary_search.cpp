bool check(int m){
	return true;
}

void binary_search(){
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
