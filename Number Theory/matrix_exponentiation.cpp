#define MOD 1000000007

vector<vector<long long> > identity;

/* O(N^3). */
vector<vector<long long> > matrix_mul(const vector<vector<long long> > &A, const vector<vector<long long> > &B){
	vector<vector<long long> > C;
	int i, j, k;

	// C will have the same number of rows as A.
	C.resize(A.size());

	// For each row of C.
	for (i = 0; i < (int)C.size(); i++){
		// C will have the same number of columns as B.
		C[i].assign(B[0].size(), 0);

		// For each column of C.
		for (j = 0; j < (int)C[i].size(); j++){
			// For each column of A or row of B.
			for (k = 0; k < (int)A[0].size(); k++){
				C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
			}
		}
	}

	return C;
}

/* O(N^3 * log(y)). */
vector<vector<long long> > matrix_exp(vector<vector<long long> > x, long long y){
	vector<vector<long long> > ans = identity; // Base case.

	// Decomposing y in binary. Multiplying the answer by x^1, x^2, x^4, x^8, ...
	while (y > 0){
		// If current bit is set.
		if (y & 1ll){
			ans = matrix_mul(ans, x);
		}

		y >>= 1ll; // Next bit.
		x = matrix_mul(x, x); // Next power of x.
	}

	return ans;
}

/* O(N^2). Fills up the Identity matrix. */
void initialize(int n){
	int i, j;

	identity.resize(n);

	for (i = 0; i < (int)identity.size(); i++){
		identity[i].resize(n);

		for (j = 0; j < (int)identity[i].size(); j++){
			identity[i][j] = (i == j);
		}
	}
}

/* O(D^3 * log(N)). Calculates f = mat^n * base - Assuming mat is DxD */
/*                                                                    */
/* F(n) = a * F(n - 1) + b * F(n - 2) + c * F(n - 3)                  */
/* | F(n + 2) |   | a b c |   | F(n + 1) |                            */
/* | F(n + 1) | = | 1 0 0 | * | F(  n  ) |                            */
/* | F(  n  ) |   | 0 1 0 |   | F(n - 1) |                            */
/*                                                                    */
/* A(n) = aa * A(n - 1) + ab * B(n - 1) + ac * C(n - 1)               */
/* B(n) = ba * A(n - 1) + bb * B(n - 1) + bc * C(n - 1)               */
/* C(n) = ca * A(n - 1) + cb * B(n - 1) + cc * C(n - 1)               */
/* | A(n) |   | aa ab ac |   | A(n - 1) |                             */
/* | B(n) | = | ba bb bc | * | B(n - 1) |                             */
/* | C(n) |   | ca cb cc |   | C(n - 1) |                             */
long long solve(vector<vector<long long> > mat, vector<vector<long long> > base, long long n){
	vector<vector<long long> > f;

	// Initializing Identity matrix.
	initialize(mat.size());

	// Matrix Exponentiation.
	mat = matrix_exp(mat, n);
	f = matrix_mul(mat, base);

	// Returning the last element (either F(n) or C(n)).
	return f[mat.size() - 1][0];
}
