/* O(N) - Use pattern#string. z[i] = the length of the longest match between
the prefix starting at s[i] and the prefix of s. */
vector<int> z(const string &s){
	vector<int> ans;
	int l, r, i;

	// Initialization.
	ans.resize(s.size());
	ans[0] = (int)s.size(); // We can ignore this value.
	l = r = 0; // Range is [L, R)

	for (i = 1; i < (int)s.size(); i++){
		if (i > r){
			l = r = i;
		}

		ans[i] = min(ans[i - l], r - i);

		while (i + ans[i] < (int)s.size() and s[i + ans[i]] == s[ans[i]]){
			ans[i]++;
			l = i;
			r = i + ans[i];
		}
	}

	return ans;
}