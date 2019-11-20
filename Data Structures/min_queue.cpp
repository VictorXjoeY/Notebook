constexpr int N = 100000;

deque<pair<int, int>> d; // Stores (p, a[p]). Both p and a[p] are strictly increasing.
int a[N + 1];

/* Amortized O(1). */
void add(int p) {
	// Removing every element with index lesser than p and value greater or equal
	// to a[p] because they can't be the minimum anymore.
	while (!d.empty() and d.back().second >= a[p]) {
		d.pop_back();
	}

	// Inserting this element at the back, at some point he might be the minimum.
	d.push_back({p, a[p]});
}

/* Amortized O(1). */
void remove(int p) {
	// Removing every element with index lesser or equal to p.
	while (!d.empty() and d.front().first <= p) {
		d.pop_front();
	}
}

/* O(1) - Returns p, the index of the minimum element. */
int query() {
	return d.front().first;
}
