/* O(N). Use pattern#string. z[i] = the length of the longest match between
the prefix starting at s[i] and the prefix of s. */
vector<int> z(string &s){
	vector<int> ans;
	int n, l, r, i;

	// Initialization.
	n = s.size();
	ans.resize(n);
	ans[0] = n; // We can ignore this value.
	l = r = 0; // Range is [L, R)

	for (i = 1; i < n; i++){
		if (i > r){
			l = r = i;
		}

		ans[i] = min(ans[i - l], r - i);

		while (i + ans[i] < n and s[i + ans[i]] == s[ans[i]]){
			ans[i]++;
			l = i;
			r = i + ans[i];
		}
	}

	return ans;
}