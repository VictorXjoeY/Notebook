#define OFFSET 'a'
#define ALPHABET_SIZE 26

struct Trie{
	int child[ALPHABET_SIZE];
	int size, terminal;

	Trie(){
		memset(this->child, -1, sizeof(this->child));
		this->size = this->terminal = 0;
	}
};

// Root of the Trie.
vector<Trie> vt = {Trie()};

/* O(|S|). */
void trie_insert(const string &s){
	int cur, i;

	for (i = 0, cur = 0; i < (int)s.size(); i++){
		vt[cur].size++;

		// If this child has not been created yet.
		if (vt[cur].child[s[i] - OFFSET] == -1){
			vt[cur].child[s[i] - OFFSET] = vt.size(); // Adding pointer.
			vt.push_back(Trie()); // Creating child.
		}

		// Moving to its child.
		cur = vt[cur].child[s[i] - OFFSET];
	}

	// At terminal node. String was completely inserted.
	vt[cur].size++;
	vt[cur].terminal++;
}

/* O(|S|). */
int trie_count(const string &s){
	int cur, i;

	for (i = 0, cur = 0; i < (int)s.size(); i++){
		// If there's no child with this character.
		if (vt[cur].child[s[i] - OFFSET] == -1){
			return 0;
		}

		// Moving to its child.
		cur = vt[cur].child[s[i] - OFFSET];
	}

	// At terminal node.
	return vt[cur].terminal;
}