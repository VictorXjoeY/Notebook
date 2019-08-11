#define OFFSET 'a'
#define ALPHABET_SIZE 26

/* O(|S|) - Use pattern#text. p[i] = the length of the longest match between
the suffix ending at s[i] and the prefix of s. */
vector<int> prefix_function(const string &s){
	vector<int> p;

	// Initialization.
	p.resize(s.size());
	p[0] = 0;

	for (int i = 1; i < (int)s.size(); i++){
		p[i] = p[i - 1];

		// While it is not possible to expand a prefix of size p[i], move to a shorter prefix.
		while (p[i] > 0 and s[i] != s[p[i]]){
			p[i] = p[p[i] - 1];
		}

		// If it is possible to expand a prefix of size p[i].
		if (s[i] == s[p[i]]){
			p[i]++;
		}
	}

	return p;
}

/* O(|S| * |Alphabet|) - Given that you have a matching prefix of size i, kmp[i][c]
stores the size of the matching prefix after appending the character c.*/
vector<vector<int>> kmp_automaton(const string &s){
	vector<vector<int>> kmp;
	vector<int> p;

	// Retrieving the prefix function of the string s.
	p = prefix_function(s);
	kmp.resize(s.size());

	// Allocating.
	for (int i = 0; i < (int)s.size(); i++){
		kmp[i].resize(ALPHABET_SIZE);
	}

	// Initializing.
	for (char c = 0; c < ALPHABET_SIZE; c++){
		kmp[0][c] = c + OFFSET == s[0];
	}

	// Calculating for every matching prefix of size i.
	for (int i = 1; i < (int)s.size(); i++){
		for (char c = 0; c < ALPHABET_SIZE; c++){
			if (c + OFFSET == s[i]){ // Can expand a prefix of size i.
				kmp[i][c] = i + 1;
			}
			else{ // Expanding a shorter string.
				kmp[i][c] = kmp[p[i - 1]][c];
			}
		}
	}

	return kmp;
}