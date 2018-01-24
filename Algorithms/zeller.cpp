// O(1) Given the date, returns the day of the week from 0 to 6 starting from Sunday.
int zeller(long long d, long long m, long long y){
	if (m == 1 or m == 2){
		m += 12;
		y--;
	}

	return (((d + ((13 * (m + 1)) / 5) + y + (y / 4) - (y / 100) + (y / 400)) % 7) + 6) % 7;
}