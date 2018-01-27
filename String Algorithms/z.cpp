#define N 100000

int z[2 * N + 2];
string s;

/* O(N). t#s.
z[i] = the length of the longest match between the prefix starting at s[i] and the prefix of s. */
void z_function(){
	int n, l, r, i;

	// [L, R)
	n = s.size();
	z[0] = n; // Ignore this value.
	l = r = 0;

	for (i = 1; i < n; i++){
		if (i > r){
			l = r = i;
		}

		z[i] = min(z[i - l], r - i);

		while (i + z[i] < n and s[i + z[i]] == s[z[i]]){
			z[i]++;
			l = i;
			r = i + z[i];
		}
	}

}