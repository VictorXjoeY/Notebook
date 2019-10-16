#define N 1000000

int mp[N + 1]; // mp[i] stores the minimum prime number which divides i. i is prime if it's not 0 and mp[i] == i.
int mobius[N + 1];

/* O(N). */
vector<int> linear_sieve(int n){
	vector<int> p; // Stores prime numbers.
	mobius[1] = 1;

	for (int i = 2; i <= n; i++){
		if (!mp[i]){ // i is prime if we haven't found any smaller factors of it.
			mobius[i] = -1;
			mp[i] = i;
			p.push_back(i);
		}

		// Since every number x can be written as x = i * mp[x] we can iterate over every prime mp[x] (prime[j]).
		for (int j = 0; j < (int)p.size() and p[j] <= mp[i] and i * p[j] <= n; j++){
			// mobius[x] = mobius[i * mp[x]] = mobius[i] * 0 if mp[x] divides i or mobius[i] * -1 if mp[x] doesn't divide i.
			mobius[i * p[j]] = mobius[i] * (p[j] == mp[i] ? 0 : -1);
			mp[i * p[j]] = p[j];
		}
	}

	return p;
}