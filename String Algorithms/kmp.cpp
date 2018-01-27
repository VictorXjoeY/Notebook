#define N 100000

int prefix[2 * N + 2];
string s;

/* O(N). t#s.
 prefix[i] = the length of the longest match between the suffix ending at s[i] and the prefix of s.*/
void kmp(){
	int n, i;

	prefix[0] = 0;
	n = s.size();

	for (i = 1; i < n; i++){
		prefix[i] = prefix[i - 1];

		while (prefix[i] > 0 and s[i] != s[prefix[i]]){
			prefix[i] = prefix[prefix[i] - 1];
		}

		if (s[i] == s[prefix[i]]){
			prefix[i] += 1;
		}
	}
}