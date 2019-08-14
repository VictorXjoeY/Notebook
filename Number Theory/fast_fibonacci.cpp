vector<vector<long long>> identity;

/* O(N^3). */
vector<vector<long long>> matrix_mul(const vector<vector<long long>> &A, const vector<vector<long long>> &B, long long m){
	vector<vector<long long>> C;

	// C will have the same number of rows as A.
	C.resize(A.size());

	// For each row of C.
	for (int i = 0; i < (int)C.size(); i++){
		// C will have the same number of columns as B.
		C[i].assign(B[0].size(), 0);

		// For each column of C.
		for (int j = 0; j < (int)C[i].size(); j++){
			// For each column of A or row of B.
			for (int k = 0; k < (int)A[0].size(); k++){
				C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % m;
			}
		}
	}

	return C;
}

/* O(N^3 * Log(B)). */
vector<vector<long long>> matrix_exp(vector<vector<long long>> a, long long b, long long m){
	vector<vector<long long>> ans = identity; // Base case.

	// Decomposing b in binary. Multiplying the answer by a^1, a^2, a^4, a^8, ...
	while (b > 0){
		// If current bit is set.
		if (b & 1ll){
			ans = matrix_mul(ans, a, m);
		}

		b >>= 1ll; // Next bit.
		a = matrix_mul(a, a, m); // Next power of a.
	}

	return ans;
}

/* O(N^2) - Fills up the Identity matrix. */
void init(int n){
	identity.resize(n);

	for (int i = 0; i < (int)identity.size(); i++){
		identity[i].resize(n);

		for (int j = 0; j < (int)identity[i].size(); j++){
			identity[i][j] = (i == j);
		}
	}
}

/* O(D^3 * Log(N)) - Calculates f = mat^n * base (mod m) - Assuming mat is DxD */
/*                                                                             */
/* F(n) = a * F(n - 1) + b * F(n - 2) + c * F(n - 3)                           */
/* | F(n + 2) |   | a b c |   | F(n + 1) |                                     */
/* | F(n + 1) | = | 1 0 0 | * | F(  n  ) |                                     */
/* | F(  n  ) |   | 0 1 0 |   | F(n - 1) |                                     */
/*                                                                             */
/* A(n) = aa * A(n - 1) + ab * B(n - 1) + ac * C(n - 1)                        */
/* B(n) = ba * A(n - 1) + bb * B(n - 1) + bc * C(n - 1)                        */
/* C(n) = ca * A(n - 1) + cb * B(n - 1) + cc * C(n - 1)                        */
/* | A(n) |   | aa ab ac |   | A(n - 1) |                                      */
/* | B(n) | = | ba bb bc | * | B(n - 1) |                                      */
/* | C(n) |   | ca cb cc |   | C(n - 1) |                                      */
long long solve(vector<vector<long long>> mat, vector<vector<long long>> base, long long n, long long m){
	vector<vector<long long>> f;

	// Initializing Identity matrix.
	init(mat.size());

	// Matrix Exponentiation.
	mat = matrix_exp(mat, n, m);
	f = matrix_mul(mat, base, m);

	// Returning the last element (either F(n) or C(n)).
	return f[mat.size() - 1][0];
}


/* O(Log(N)). */
long long fibonacci(long long n){
	vector<vector<long long>> mat, base;

	// Filling Fibonacci matrix.
	mat.resize(2);
	mat[0].resize(2);
	mat[1].resize(2);
	mat[0][0] = 1;
	mat[0][1] = 1;
	mat[1][0] = 1;
	mat[1][1] = 0;

	// Filling base case.
	base.resize(2);
	base[0].resize(1);
	base[1].resize(1);
	base[0][0] = 1;
	base[1][0] = 0;

	return solve(mat, base, n);
}
