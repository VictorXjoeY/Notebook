int month[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int zeller(long long d, long long m, long long y){
	if (m == 1 or m == 2){
		m += 12;
		y--;
	}

	return (((d + ((13 * (m + 1)) / 5) + y + (y / 4) - (y / 100) + (y / 400)) % 7) + 6) % 7;
}

bool leap_year(long long y){
	return (y % 4 == 0 and y % 100 != 0) or y % 400 == 0;
}

void update(int &d, int &m, long long &y){
	if (d == month[leap_year(y)][m]){
		d = 1;

		if (m == 12){
			m = 1;
			y++;
		}
		else{
			m++;
		}
	}
	else{
		d++;
	}
}