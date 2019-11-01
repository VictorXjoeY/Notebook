constexpr int N = 100000;

// Remember to use highest_freq[find_set(u)] and freq[find_set(u)] to access the answer related to u's component.
unordered_map<int, int> freq[N + 1];
int highest_freq[N + 1]; // Frequency of most frequent.
int size[N + 1];
int p[N + 1];
int num_sets;
int a[N + 1]; // (Input)
int n; // (Input)

/* O(Log(N)). */
int find_set(int u) {
	if (u == p[u]) { // Found representative.
		return u;
	}

	// Search for the set's representative without compressing.
	return find_set(p[u]);
}

/* O(size[src]). */
void merge(int dest, int src) {
	unordered_map<int, int>::iterator it;

	// Updating parent link and size of the set.
	p[src] = dest;
	size[dest] += size[src];

	// Merging.
	for (it = freq[src].begin(); it != freq[src].end(); it++) {
		freq[dest][it->first] += it->second;
		highest_freq[dest] = max(highest_freq[dest], freq[dest][it->first]);
	}
}

/* Amortized O(Log(N)). */
void union_set(int u, int v) {
	// Finding representatives of u and v.
	int x = find_set(u);
	int y = find_set(v);

	// If u and v belong to different sets.
	if (x != y) {
		// Attaching the smaller tree to the bigger tree.
		if (size[x] < size[y]) {
			merge(y, x);
		}
		else {
			merge(x, y);
		}

		// Decreasing number of sets.
		num_sets--;
	}
}

/* O(N). */
void init() {
	num_sets = n;

	// Making sets of size 1.
	for (int i = 1; i <= n; i++) {
		p[i] = i;
		size[i] = 1;
		freq[i].clear();
		freq[i][a[i]] = 1;
		highest_freq[i] = 1;
	}
}