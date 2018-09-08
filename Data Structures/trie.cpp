struct Trie{
	int child[26];
	int terminal;

	Trie(){
		memset(child, -1, sizeof(child));
		terminal = 0;
	}
};

// Root of the Trie.
vector<Trie> vt = {Trie()};

/* O(|S|). */
void trie_insert(int cur, const string &s, int p){
	// String was completely inserted.
	if (p == (int)s.size()){
		vt[cur].terminal++;
		return;
	}

	// If this child has not been created yet.
	if (vt[cur].child[s[p] - 'a'] == -1){
		// Adding pointer.
		vt[cur].child[s[p] - 'a'] = vt.size();

		// Creating child.
		vt.push_back(Trie());
	}

	// Recursive call to its child.
	trie_insert(vt[cur].child[s[p] - 'a'], s, p + 1);
}

/* O(|S|). */
int trie_count(int cur, const string &s, int p){
	// String completely processed, returning number of terminals in this position.
	if (p == (int)s.size()){
		return vt[cur].terminal;
	}

	// If this child has not been created, the answer is 0.
	if (vt[cur].child[s[p] - 'a'] == -1){
		return 0;
	}

	// Recursive call to its child.
	return trie_count(vt[cur].child[s[p] - 'a'], s, p + 1);
}