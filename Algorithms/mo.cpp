int sq;

struct Query{
	int idx, ans, l, r;

	Query(){}

	Query(int idx, int l, int r){
		this->idx = idx;
		this->ans = 0;
		this->l = l;
		this->r = r;
	}

	bool operator < (const Query &b) const{
		if (l / sq == b.l / sq){
			return r < b.r;
		}

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

void sqrt_decomposition(){
	int i;

	for (i = 0; i < n; i++){
		if (i * i <= n){
			sq = i;
		}
	}

	for (i = 0; i < m; i++){
		p[i] = i;
	}

	sort(q, q + m);
	sort(p, p + m, comp);

	l = 0;
	r = -1;

	for (i = 0; i < m; i++){
		while (l < q[i].l){
			remove(a[l]);
			l++;
		}

		while (l > q[i].l){
			l--;
			add(a[l]);
		}

		while (r < q[i].r){
			r++;
			add(a[r]);
		}

		while (r > q[i].r){
			remove(a[r]);
			r--;
		}

		q[i].ans = 0;
	}

	for (i = 0; i < m; i++){
		printf("%d\n", q[p[i]].ans);
	}
}