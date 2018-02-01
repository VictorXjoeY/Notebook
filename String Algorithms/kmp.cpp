/* O(N). Use pattern#string. prefix[i] = the length of the longest match between
the suffix ending at s[i] and the prefix of s. */
vector<int> kmp(string &s){
	vector<int> ans;
	int n, i;

	// Initialization.
	n = s.size();
	ans.resize(n);
	ans[0] = 0;

	for (i = 1; i < n; i++){
		ans[i] = ans[i - 1];

		while (ans[i] > 0 and s[i] != s[ans[i]]){
			ans[i] = ans[ans[i] - 1];
		}

		if (s[i] == s[ans[i]]){
			ans[i] += 1;
		}
	}

	return ans;
}