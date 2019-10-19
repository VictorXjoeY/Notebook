constexpr int N = 1000000;

int mp[N + 1]; // mp[i] stores the minimum prime number which divides i. i is prime if it's not 0 and mp[i] == i.

/* O(N). */
vector<int> linear_sieve(int n){
	vector<int> p; // Stores prime numbers.

	for (int i = 2; i <= n; i++){
		if (!mp[i]){ // i is prime if we haven't found any smaller factors of it.
			mp[i] = i;
			p.push_back(i);
		}

		// Since every number x can be written as x = i * mp[x] we can iterate over every prime mp[x] (prime[j]).
		for (int j = 0; j < p.size() and p[j] <= mp[i] and i * p[j] <= n; j++){
			mp[i * p[j]] = p[j];
		}
	}

	return p;
}

/* O(Log(N)). */
vector<pair<int, int>> factor(int n){
	vector<pair<int, int>> f; // Sorted vector of pairs (prime, exponent).

	// Asserting that linear_sieve was executed before factorizing.
	assert(mp[2] == 2);

	// While there are still prime factors.
	while (n > 1){
		if (!f.empty() and mp[n] == f.back().first){
			f.back().second++;
		}
		else{
			f.push_back({mp[n], 1});
		}

		// Dividing n by its smallest prime factor.
		n /= mp[n];
	}

	return f;
}