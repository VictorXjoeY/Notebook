#define OFFSET 'a'
#define ALPHABET_SIZE 26

struct AhoCorasick{
	int child[ALPHABET_SIZE], dp[ALPHABET_SIZE];
	int terminal, suffix_link;

	AhoCorasick(){
		memset(this->child, 0, sizeof(this->child));
		memset(this->dp, 0, sizeof(this->dp));
		this->terminal = this->suffix_link = 0;
	}
};

// Root of the Trie.
vector<AhoCorasick> vt = {AhoCorasick()};

/* O(|P|). */
void aho_corasick_insert(const string &s){
	int u, i;

	for (i = 0, u = 0; i < (int)s.size(); i++){
		// If this child has not been created yet.
		if (vt[u].child[s[i] - OFFSET] == 0){
			vt[u].child[s[i] - OFFSET] = vt.size(); // Adding pointer.
			vt.push_back(AhoCorasick()); // Creating child.
		}

		// Moving to its child.
		u = vt[u].child[s[i] - OFFSET];
	}

	// At terminal node. String was completely inserted.
	vt[u].terminal++;
}

// O(1) - Returns the merged results for two nodes.
int merge(int u, int v){
	return vt[u].terminal + vt[v].terminal;
}

/* O(sum(|P|) * |Alphabet|). */
void aho_corasick_build(){
	int u, v, p, c;
	queue<int> q;

	// Pushing root.
	q.push(0);

	// Breadth-First Search.
	while (!q.empty()){
		u = q.front();
		q.pop();

		for (c = 0; c < ALPHABET_SIZE; c++){
			v = vt[u].child[c]; // Direct child.
			p = vt[u].suffix_link; // Will store parent of suffix link or 0.

			while (p != 0 and vt[p].child[c] == 0){
				p = vt[p].suffix_link;
			}

			if (v == 0){ // No direct child.
				if (vt[p].child[c] == 0){ // Has to start all over.
					vt[u].dp[c] = 0;
				}
				else{ // Can extend p.
					vt[u].dp[c] = vt[p].child[c];
				}
			}
			else{ // Has child.
				vt[u].dp[c] = v; // Trivial extension.

				if (vt[p].child[c] == 0){ // Has to start all over.
					vt[v].suffix_link = 0;
				}
				else{ // Found a longest proper suffix.
					vt[v].suffix_link = u == 0 ? 0 : vt[p].child[c];
				}

				// Merging the results this nodes longest proper suffix with itself.
				vt[v].terminal = merge(v, vt[v].suffix_link);

				q.push(v);
			}
		}
	}
}