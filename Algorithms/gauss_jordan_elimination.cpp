/* O(N^3) - Performs row reduction on an Augmented Matrix A. A has N rows and M + 1 columns. */
/* The Augmented Matrix of a system of linear equations Ax = b is obtained by concatenating A with b (A|b). */
void gauss_jordan_elimination(double **A, int n, int m){
	int i, j, k, l;

	// Gauss-Jordan Elimination.
	for (i = 1, j = 1; i <= n; i++, j++){
		// Searching for the next pivot A[i][j].
		while (j <= m + 1 && A[i][j] == 0.0){
			// Searching for a row k below A[i][j] such that A[k][j] != 0.
			for (k = i + 1; k <= n; k++){
				if (A[k][j] != 0.0){
					break;
				}
			}

			// Checking if a pivot was found.
			if (k <= n){ // Pivot was found.
				swap(A[i], A[k]);
			}
			else{ // Pivot wasn't found.
				j++;
			}
		}

		// There are no pivots left.
		if (j > m + 1){
			break;
		}

		// Dividing the i-th row by the pivot A[i][j].
		for (k = j + 1; k <= m + 1; k++){
			A[i][k] /= A[i][j];
		}

		// The value of the pivot is 1 after the division.
		A[i][j] = 1.0;

		// Eliminating all the other entries of the j-th column.
		for (k = 1; k <= n; k++){
			// If it's not the i-th row (pivot's row) and it has an entry different from 0.
			if (k != i && A[k][j] != 0.0){
				// Subtracting the i-th row out of the k-th row.
				for (l = j + 1; l <= m + 1; l++){
					A[k][l] -= A[k][j] * A[i][l];
				}

				// The value of A[k][j] is 0 after the subtraction.
				A[k][j] = 0.0;
			}
		}
	}
}