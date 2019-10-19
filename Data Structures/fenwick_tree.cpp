// n = number of elements
// m = max element
class FenwickTree{
private:
	vector<int> ft;
	int m;

	// Least Significant One.
	inline int LSOne(int x){
		return (x & (-x));
	}

	// Range Sum Query [1..r].
	int query(int r){
		int sum = 0;

		while (r){
			sum += ft[r];
			r -= LSOne(r);
		}

		return sum;
	}

public:
	FenwickTree(){}

	FenwickTree(int m){
		this->m = m;
		ft.assign(m + 1, 0);
	}

	// Range Sum Query [l..r].
	int query(int l, int r){
		return query(r) - query(l - 1);
	}

	// Adjust point p by x.
	void update(int p, int x){
		while (p < ft.size()){
			ft[p] += x;
			p += LSOne(p);
		}
	}
};