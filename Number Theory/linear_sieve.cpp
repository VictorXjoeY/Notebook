#define N 1000000

int mp[N + 1]; // mp[i] stores the minimum prime number which divides i. i is prime if it's not 0 and mp[i] == i.
vector<int> p; // Stores prime numbers.

/* O(N). */
void linear_sieve(){
	for (int i = 2; i <= N; i++){
		if (!mp[i]){ // i is prime if we haven't found any smaller factors of it.
			mp[i] = i;
			p.push_back(i);
		}

		// Since every number x can be written as x = i * mp[x] we can iterate over every prime mp[x] (prime[j]).
		for (int j = 0; j < (int)p.size() and p[j] <= mp[i] and i * p[j] <= N; j++){
			mp[i * p[j]] = p[j];
		}
	}
}