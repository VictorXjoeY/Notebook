class UnionFind{
private:
	vector<int> p, rank, size;
	int n;
public:
	UnionFind(){}

	UnionFind(int n){
		int i;

		size.assign(n, 1);
		rank.assign(n, 0);
		p.resize(n);
		this->n = n;

		for (i = 0; i < n; i++){
			p[i] = i;
		}
	}

	int findSet(int u){
		if (u == p[u]){
			return u;
		}

		return p[u] = findSet(p[u]);
	}

	void unionSet(int u, int v){
		int x, y;

		x = findSet(u);
		y = findSet(v);

		if (x != y){
			if (rank[x] > rank[y]){
				size[x] += size[y];
				p[y] = x;
			}
			else{
				size[y] += size[x];
				p[x] = y;

				if (rank[x] == rank[y]){
					rank[y]++;
				}
			}

			n--;
		}
	}

	int numSets(){
		return n;
	}

	int setSize(int u){
		return size[findSet(u)];
	}
};

struct Edge{
	int u, v, w;

	Edge(){

	}

	Edge(int u, int v, int w){
		this->u = u;
		this->v = v;
		this->w = w;
	}

	bool operator < (const Edge &b) const{
		return w < b.w;
	}
};

Edge e[N + 1];
int n, m;

int kruskal(){
	UnionFind uf;
	int ans, i;

	uf = UnionFind(n);
	sort(e, e + m);
	ans = 0;

	for (i = 0; i < m; i++){
		if (uf.findSet(e[i].u) != uf.findSet(e[i].v)){
			uf.unionSet(e[i].u, e[i].v);
			ans += e[i].w;
		}
	}

	return ans;
}