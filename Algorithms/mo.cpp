#define N 100000
#define M 100000
#define SQ (int)sqrt(N)

struct Query{
	int idx, l, r;

	Query(){}

	Query(int idx, int l, int r){
		this->idx = idx;
		this->l = l;
		this->r = r;
	}

	bool operator < (const Query &b) const{
		// If they belong to the same bucket, sort by r.
		if (l / SQ == b.l / SQ){
			return r < b.r;
		}

		// Sort by bucket.
		return l / SQ < b.l / SQ;
	}
};

Query q[M + 1]; // (Input)
int ans[M + 1];
int a[N + 1]; // (Input)
int n, m; // (Input)

void remove(int p){
	// Define this function.
}

void add(int p){
	// Define this function.
}

/* O(Q * log(Q) + Q * sqrt(N)). */
void mo(){
	int l, r;

	// Sorting queries.
	sort(q + 1, q + 1 + m);

	// Starting from empty range.
	l = 1;
	r = 0;

	// For every query.
	for (int i = 1; i <= m; i++){
		// Adjusting up r.
		while (r < q[i].r){
			r++;
			add(r);
		}

		// Adjusting down r.
		while (r > q[i].r){
			remove(r);
			r--;
		}

		// Adjusting up l.
		while (l < q[i].l){
			remove(l);
			l++;
		}

		// Adjusting down l.
		while (l > q[i].l){
			l--;
			add(l);
		}

		// Saving the answer for this query.
		ans[q[i].idx] = 0;
	}
}