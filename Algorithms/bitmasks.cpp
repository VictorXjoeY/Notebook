/* O(1) - Sets the i'th bit to 1. */
long long set(long long mask, long long i){
	return mask | (1ll << i);
}

/* O(1) - Sets the i'th bit to 0. */
long long reset(long long mask, long long i){
	return mask & ~(1ll << i);
}

/* O(1) - Toggles the i'th bit. */
long long toggle(long long mask, long long i){
	return mask ^ (1ll << i);
}

/* O(1) - Checks if the i'th bit is set. */
bool is_set(long long mask, long long i){
	return (mask >> i) & 1ll;
}

/* O(1) - Returns the number of bits that are set. */
long long count(long long mask){
	return __builtin_popcountll(mask);
}

/* O(1) - Retrieves the Least Significant Bit. */
long long lsb(long long mask){
	return mask & (-mask);
}

/* O(1) - Retrieves the index of the Most Significant Bit. */
long long msb_index(long long mask){
	return 8ll * sizeof(mask) - __builtin_clzll(mask) - 1ll;
}

/* O(1) - Retrieves the Most Significant Bit. */
long long msb(long long mask){
	if (mask == 0){
		return 0;
	}

	return 1ll << msb_index(mask);
}