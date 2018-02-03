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

	int findSet(int u){
		// Found representative.
		if (u == p[u]){
			return u;
		}

		// Compressing the path as we search for the set's representative.
		return p[u] = findSet(p[u]);
	}

	void unionSet(int u, int v){
		int x, y;

		// Finding representatives of u and v.
		x = findSet(u);
		y = findSet(v);

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

	int numSets(){
		return n;
	}

	int setSize(int u){
		return size[findSet(u)];
	}
};