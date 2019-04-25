#define N 1000

#define TOP_LEFT(x) (4 * x + 1)
#define TOP_RIGHT(x) (4 * x + 2)
#define BOTTOM_LEFT(x) (4 * x + 3)
#define BOTTOM_RIGHT(x) (4 * x + 4)

int quad[4 * N * N + 1];
int mat[N + 1][N + 1]; // (Input)

int merge(int ntl, int ntr, int nbl, int nbr){
	return max(max(ntl, ntr), max(nbl, nbr));
}

void build(int cur, int xmin, int xmax, int ymin, int ymax){
	int xmid, ymid;

	xmid = (xmin + xmax) / 2;
	ymid = (ymin + ymax) / 2;

	// Invalid.
	if (xmin > xmax or ymin > ymax){
		return;
	}

	// Leaf.
	if (xmin == xmax and ymin == ymax){
		quad[cur] = mat[xmin][ymin];
		return;
	}

	// Going down all the ways.
	build(TOP_LEFT(cur), xmin, xmid, ymin, ymid);
	build(TOP_RIGHT(cur), xmin, xmid, ymid + 1, ymax);
	build(BOTTOM_LEFT(cur), xmid + 1, xmax, ymin, ymid);
	build(BOTTOM_RIGHT(cur), xmid + 1, xmax, ymid + 1, ymax);

	// Merging children's results.
	quad[cur] = merge(quad[TOP_LEFT(cur)], quad[TOP_RIGHT(cur)], quad[BOTTOM_LEFT(cur)], quad[BOTTOM_RIGHT(cur)]);
}

void update(int cur, int xmin, int xmax, int ymin, int ymax, int x, int y, int val){
	int xmid, ymid;

	xmid = (xmin + xmax) / 2;
	ymid = (ymin + ymax) / 2;

	// Invalid.
	if (xmin > xmax or ymin > ymax){
		return;
	}

	// Out of range.
	if (xmin > x or xmax < x or ymin > y or ymax < y){
		return;
	}

	// Leaf.
	if (xmin == xmax and ymin == ymax){
		quad[cur] += val;
		return;
	}

	// Going down all the ways.
	update(TOP_LEFT(cur), xmin, xmid, ymin, ymid, x, y, val);
	update(TOP_RIGHT(cur), xmin, xmid, ymid + 1, ymax, x, y, val);
	update(BOTTOM_LEFT(cur), xmid + 1, xmax, ymin, ymid, x, y, val);
	update(BOTTOM_RIGHT(cur), xmid + 1, xmax, ymid + 1, ymax, x, y, val);

	// Merging children's results.
	quad[cur] = merge(quad[TOP_LEFT(cur)], quad[TOP_RIGHT(cur)], quad[BOTTOM_LEFT(cur)], quad[BOTTOM_RIGHT(cur)]);
}

int query(int cur, int xmin, int xmax, int ymin, int ymax, int imin, int imax, int jmin, int jmax){
	int ntl, ntr, nbl, nbr, xmid, ymid;

	xmid = (xmin + xmax) / 2;
	ymid = (ymin + ymax) / 2;

	// Invalid.
	if (xmin > xmax or ymin > ymax){
		return;
	}

	// Out of range.
	if (xmin > x or xmax < x or ymin > y or ymax < y){
		return;
	}

	// Leaf.
	if (xmin == xmax and ymin == ymax){
		quad[cur] += val;
		return;
	}

	// Going down all the ways.
	ntl = query(TOP_LEFT(cur), xmin, xmid, ymin, ymid, imin, imax, jmin, jmax);
	ntr = query(TOP_RIGHT(cur), xmin, xmid, ymid + 1, ymax, imin, imax, jmin, jmax);
	nbl = query(BOTTOM_LEFT(cur), xmid + 1, xmax, ymin, ymid, imin, imax, jmin, jmax);
	nbr = query(BOTTOM_RIGHT(cur), xmid + 1, xmax, ymid + 1, ymax, imin, imax, jmin, jmax);

	// Merging the query results.
	return merge(ntl, ntr, nbl, nbr);
}