// n = number of elements
// m = max element
class FenwickTree {
private:
	vector<int> ft;
	int m;

	/* O(1) - Retrieves the Least Significant Bit. */
	int lsb(int mask) {
		return mask & (-mask);
	}

	/* O(log(R)) - Range Sum Query [1..r]. */
	int query(int r) {
		int sum = 0;

		while (r) {
			sum += ft[r];
			r -= lsb(r);
		}

		return sum;
	}

public:
	FenwickTree() {}

	/* O(N). */
	FenwickTree(int m) {
		this->m = m;
		ft.assign(m + 1, 0);
	}

	/* O(log(L) + log(R)) - Range Sum Query [l..r]. */
	int query(int l, int r) {
		return query(r) - query(l - 1);
	}

	/* O(P) - Adjust point p by x. */
	void update(int p, int x) {
		while (p < ft.size()) {
			ft[p] += x;
			p += lsb(p);
		}
	}
};
