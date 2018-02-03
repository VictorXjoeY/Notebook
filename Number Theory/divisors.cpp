/* O(sqrt(N)). */
vector<long long> divisors(long long n){
	vector<long long> d;
	long long i;

	// For every i up to sqrt(n).
	for (i = 1; i * i <= n; i++){
		// If i divides n.
		if (n % i == 0){
			if (i * i == n){
				// Pushing i.
				d.push_back(i);
			}
			else{
				// Pushing i and n / i.
				d.push_back(i);
				d.push_back(n / i);
			}
		}
	}

	return d;
}
