// 0-based Union Find with Path Compression
class UnionFind{
private:
	vector<int> p, rank, size;
	int n;
public:
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