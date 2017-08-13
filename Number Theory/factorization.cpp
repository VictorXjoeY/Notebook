for (i = 2; i * i <= n; i++){
	while (n % i == 0){
		n /= i;
		f[i]++;
	}
}

if (n > 1){
	f[n]++;
}