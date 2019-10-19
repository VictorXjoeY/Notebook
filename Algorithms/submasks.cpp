void f(int submask) {
	// Do something with submask.
}

/* O(|Number of submasks|). */
void submasks(int mask) {
	// Going through all the non-empty submasks in decreasing order of value.
	for (int submask = mask; submask; submask = (submask - 1) & mask) {
		f(submask);
	}

	// Processing the empty submask as well.
	f(0);
}

/* O(3^n) - Goes through all the masks with n bits and its submasks. */
void masks_and_submasks(int n) {
	for (int mask = 0; mask < (1 << n); mask++) {
		submasks(mask);
	}
}