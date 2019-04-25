#define M 100000

class UnionFind{
private:
	vector<int> p, rank, size;
	int n;
public:
	UnionFind(){}

	UnionFind(int n){
		int i;

		// Initializing.
		size.assign(n, 1); // Size of sets is 1 initially.
		rank.assign(n, 0); // Rank of sets is 0 initially.
		p.resize(n);
		this->n = n;

		// Setting the representative to be itself for each set.
		for (i = 0; i < n; i++){
			p[i] = i;
		}
	}

	/* O(1). */
	int find_set(int u){
		// Found representative.
		if (u == p[u]){
			return u;
		}

		// Compressing the path as we search for the set's representative.
		return p[u] = find_set(p[u]);
	}

	/* O(1). */
	void union_set(int u, int v){
		int x, y;

		// Finding representatives of u and v.
		x = find_set(u);
		y = find_set(v);

		// If u and v belong to different sets.
		if (x != y){
			if (rank[x] > rank[y]){ // Attaching y's tree to the root x.
				size[x] += size[y];
				p[y] = x;
			}
			else if (rank[x] < rank[y]){ // Attaching x's tree to the root y.
				size[y] += size[x];
				p[x] = y;
			}
			else{ // Can attach either one. Attaching y's tree to the root x. Rank increases by one.
				size[x] += size[y];
				p[y] = x;
				rank[x]++;
			}

			// Decreasing number of sets.
			n--;
		}
	}

	/* O(1). */
	int num_sets(){
		return n;
	}

	/* O(1). */
	int set_size(int u){
		return size[find_set(u)];
	}
};

struct Edge{
	int u, v, w;

	Edge(){}

	Edge(int u, int v, int w){
		this->u = u;
		this->v = v;
		this->w = w;
	}

	bool operator < (const Edge &b) const{
		return w < b.w;
	}
};

Edge e[M + 1]; // (Input)
int n, m; // (Input)

/* O(E * Log(E)). */
int kruskal(){
	UnionFind uf;
	int ans, i;

	// Creating a Union Find data structure with sets from 0 to n.
	uf = UnionFind(n + 1);

	// Sorting edges according to their weights.
	sort(e + 1, e + 1 + m);
	ans = 0;

	// For every edge (u, v).
	for (i = 1; i <= m; i++){
		// If vertex u and vertex v belongs to different sets.
		if (uf.findSet(e[i].u) != uf.findSet(e[i].v)){
			// Edge (u, v) belongs to the Minimum Spanning Tree. Unite u's set with v's set.
			uf.unionSet(e[i].u, e[i].v);
			ans += e[i].w;
		}
	}

	return ans;
}