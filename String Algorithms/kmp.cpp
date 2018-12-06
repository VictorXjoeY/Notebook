/* O(N). Use pattern#string. prefix[i] = the length of the longest match between
the suffix ending at s[i] and the prefix of s. */
vector<int> kmp(const string &s){
	vector<int> ans;
	int i;

	// Initialization.
	ans.resize(s.size());
	ans[0] = 0;

	for (i = 1; i < (int)s.size(); i++){
		ans[i] = ans[i - 1];

		while (ans[i] > 0 and s[i] != s[ans[i]]){
			ans[i] = ans[ans[i] - 1];
		}

		if (s[i] == s[ans[i]]){
			ans[i]++;
		}
	}

	return ans;
}