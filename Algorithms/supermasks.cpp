void f(int supermask) {
	// Do something with supermask.
}

/* O(|Number of supermasks with n bits|). */
void supermasks(int mask, int n) {
	int complement = ((1 << n) - 1) ^ mask;

	// Going through all the non-empty submasks of the complement in decreasing order of value.
	for (int submask = complement; submask; submask = (submask - 1) & complement) {
		f(submask | mask);
	}

	// Processing the mask itself as well.
	f(0 | mask);
}

/* O(3^n) - Goes through all the masks with n bits and its supermasks. */
void masks_and_supermasks(int n) {
	for (int mask = 0; mask < (1 << n); mask++) {
		supermasks(mask, n);
	}
}