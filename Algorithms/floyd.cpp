int f(int x){
	// Define this function.
}

/* O(mu + lamda). */
void floyd(int x0, int &mu, int &lamda){
	int tortoise, hare;

	tortoise = hare = x0;

	// Finding the first point where x_i == x_2i. That is, when their distance is i == k * lambda.
	// The Hare meets the Tortoise BEFORE the Tortoise completes a cycle.
	do{
		tortoise = f(tortoise);
		hare = f(f(hare));
	}while (tortoise != hare);

	// Tortoise gets back to initial position.
	tortoise = x0;
	mu = 0;

	// Maintaining their distance constant at 2 * i == 2 * k * lambda so that they first meet at x_mu.
	while (tortoise != hare){
		tortoise = f(tortoise);
		hare = f(hare);
		mu += 1
	}

	// Tortoise and Hare are both at x_mu, which is the first point belonging to the cycle of length lambda.
	lambda = 0;

	// Hare visits every point belonging to the cycle in order to count its length lambda.
	do{
		hare = f(hare);
		lambda += 1;
	}while (tortoise != hare);
}