#define N 1000000

bool prime[N + 1];
vector<int> p;

void sieve(int n){
	int i, j;

	memset(prime, true, sizeof(prime));
	prime[0] = prime[1] = false;

	for (i = 2; i * i <= n; i++){
		if (prime[i]){
			for (j = i * i; j <= n; j += i){
				prime[j] = false;
			}
		}
	}

	for (i = 2; i <= n; i++){
		if (prime[i]){
			p.push_back(i);
		}
	}
}