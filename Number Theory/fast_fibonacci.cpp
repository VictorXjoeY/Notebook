#define MOD 1000000007

void multiply(long long F[2][2], long long M[2][2]);
void power(long long F[2][2], long long n);
 
long long fib(long long n){
	long long F[2][2] = {{1, 1}, {1, 0}};

	if (n == 0){
		return 0;
	}

	power(F, n - 1);

	return F[0][0];
}
 
void power(long long F[2][2], long long n){
	long long M[2][2] = {{1, 1}, {1, 0}};
	
	if (n == 0 or n == 1){
		return;
	}

	power(F, n / 2);
	multiply(F, F);

	if (n % 2){
		multiply(F, M);
	}
}
 
void multiply(long long F[2][2], long long M[2][2]){
	long long x, y, z, w;

	x = (F[0][0] * M[0][0] + F[0][1] * M[1][0]) % MOD;
	y = (F[0][0] * M[0][1] + F[0][1] * M[1][1]) % MOD;
	z = (F[1][0] * M[0][0] + F[1][1] * M[1][0]) % MOD;
	w = (F[1][0] * M[0][1] + F[1][1] * M[1][1]) % MOD;

	F[0][0] = x;
	F[0][1] = y;
	F[1][0] = z;
	F[1][1] = w;
}