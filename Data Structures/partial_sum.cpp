int p[N + 1];

// O(1) - Sums "value" to every element in the range [left, right].
void update(int left, int right, int value){
	p[left] += value;
	p[right + 1] -= value;
}

// O(n) - Calculates the resulting array.
void query(){
	int i;

	v[0] += p[0];

	for (i = 1; i < n; i++){
		p[i] += p[i - 1];
		v[i] += p[i];
	}
}