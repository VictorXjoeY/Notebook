int p[N + 2];
int a[N + 2];
int n;

/* O(1) - Sums "value" to every element in the range [left, right] in a lazy way. */
void update(int left, int right, int value){
	p[left] += value;
	p[right + 1] -= value;
}

/* O(N) - Flushes all updates into array a. */
void query(){
	for (int i = 1; i <= n; i++){
		p[i] += p[i - 1];
		a[i] += p[i];
	}

	memset(p, 0, sizeof(p));
}