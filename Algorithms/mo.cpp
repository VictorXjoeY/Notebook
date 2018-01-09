#define N 100000
#define M 100000

int sq;

struct Query{
	int idx, ans, l, r;

	Query(){}

	Query(int idx, int l, int r){
		this->idx = idx;
		this->l = l;
		this->r = r;

		this->ans = 0;
	}

	bool operator < (const Query &b) const{
		// If they belong to the same bucket, sort by r.
		if (l / sq == b.l / sq){
			return r < b.r;
		}

		// Sort by bucket.
		return l / sq < b.l / sq;
	}
};

Query q[M + 1];
int a[N + 1];
int p[N + 1];
int n, m;

void remove(int x){

}

void add(int x){

}

bool comp(int x, int y){
	return q[x].idx < q[y].idx;
}

/* O(Q * log(Q) + Q * sqrt(N)). */
void mo(){
	int i;

	// Obtaining the integer square root of n.
	for (i = 0; i < n; i++){
		if (i * i <= n){
			sq = i;
		}
	}

	// Initializing vector p of indexes.
	for (i = 0; i < m; i++){
		p[i] = i;
	}

	// Sorting queries and indexes.
	sort(q, q + m);
	sort(p, p + m, comp);

	// Starting from empty range.
	l = 0;
	r = -1;

	// For every query.
	for (i = 0; i < m; i++){
		// Adjusting up l.
		while (l < q[i].l){
			remove(a[l]);
			l++;
		}

		// Adjusting down l.
		while (l > q[i].l){
			l--;
			add(a[l]);
		}

		// Adjusting up r.
		while (r < q[i].r){
			r++;
			add(a[r]);
		}

		// Adjusting down r.
		while (r > q[i].r){
			remove(a[r]);
			r--;
		}

		// Saving the answer for this query.
		q[i].ans = 0;
	}

	// Printing the answer to the queries in order.
	for (i = 0; i < m; i++){
		printf("%d\n", q[p[i]].ans);
	}
}