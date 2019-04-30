/* O(|S|) - Use pattern#text. z[i] = the length of the longest match between
the prefix starting at s[i] and the prefix of s. */
vector<int> z_function(const string &s){
	vector<int> z;
	int l, r, i;

	// Initialization.
	z.resize(s.size());
	z[0] = (int)s.size(); // We can ignore this value.
	l = r = 0; // Range is [L, R)

	for (i = 1; i < (int)s.size(); i++){
		if (i > r){
			l = r = i;
		}

		z[i] = min(z[i - l], r - i);

		while (i + z[i] < (int)s.size() and s[i + z[i]] == s[z[i]]){
			z[i]++;
			l = i;
			r = i + z[i];
		}
	}

	return z;
}