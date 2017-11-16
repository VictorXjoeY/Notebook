// 0-based Union Find
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

	// Retrieves the representative of the set contaning u.
	int findSet(int u){
		if (u == p[u]){
			return u;
		}

		return p[u] = findSet(p[u]);
	}

	// Unites the sets containing u and v.
	void unionSet(int u, int v){
		int x, y;

		// Retrieving representatives.
		x = findSet(u);
		y = findSet(v);

		if (x != y){
			if (rank[x] > rank[y]){ // x will be the parent of y.
				size[x] += size[y];
				p[y] = x;
			}
			else{ // y will be the parent of x.
				size[y] += size[x];
				p[x] = y;

				// Length of both trees are equal.
				if (rank[x] == rank[y]){
					rank[y]++;
				}
			}

			// Decreasing number of sets.
			n--;
		}
	}

	// Returns the number of sets.
	int numSets(){
		return n;
	}

	// Returns the size of the set containing u.
	int setSize(int u){
		return size[findSet(u)];
	}
};