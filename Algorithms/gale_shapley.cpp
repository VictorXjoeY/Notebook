#define N 1000

int men_pref[N + 1][N + 1]; // (Input) men_pref[i][1...n] stores the preference list of the i'th man.
int women_pref[N + 1][N + 1]; // (Input) women_pref[i][1...n] stores the preference list of the i'th woman.
int women_pref_pos[N + 1][N + 1]; // women_pref_pos[i][x] stores the position of the x'th man in the preference list of the i'th woman.
int last_proposal[N + 1]; // last_proposal[i] stores the index j such that men_pref[i][j] was the last woman proposed by the i'th man.
int women_match[N + 1]; // women_match[i] stores the index of the man matched with the i'th woman.
int men_match[N + 1]; // men_match[i] stores the index of the man matched with the i'th woman.
queue<int> available_men; // Stores the men which are still available (with men_match value 0). Could be any data structure.
int n; // (Input)

/* O(N^2) - Gale Shapley algorithm to produce a Stable Matching between n men and n women. */
void gale_shapley(){
	int k, x, y;

	// Initializing.
	memset(last_proposal, 0, sizeof(last_proposal));
	memset(women_match, 0, sizeof(women_match));
	memset(men_match, 0, sizeof(men_match));

	// For each woman i.
	for (int i = 1; i <= n; i++){
		// Pre-calculating the position of each man x in the preference list of the woman i.
		for (int j = 1; j <= n; j++){
			x = women_pref[i][j];
			women_pref_pos[i][x] = j;
		}
	}

	// Marking all men as available.
	for (int i = 1; i <= n; i++){
		available_men.push(i);
	}

	// While there are still available men.
	while (!available_men.empty()){
		// Retrieving any available man x.
		x = available_men.front();
		available_men.pop();

		// Retrieving the first woman y such that the man x hasn't proposed to yet.
		last_proposal[x]++;
		y = men_pref[x][last_proposal[x]];

		if (women_match[y]){ // If the woman y is already taken by the man k.
			k = women_match[y];

			if (women_pref_pos[y][x] < women_pref_pos[y][k]){ // If the woman y prefers the man x over the man k. Accepts proposal.
				// Matching the man x with the woman y.
				men_match[x] = y;
				women_match[y] = x;

				// The man k is now available.
				men_match[k] = 0;
				available_men.push(k);
			}
			else{ // If the woman y prefers the man k over the man x. Rejects proposal.
				available_men.push(x);
			}
		}
		else{ // If the woman y is not taken.
			// Matching the man x with the woman y.
			men_match[x] = y;
			women_match[y] = x;
		}
	}
}