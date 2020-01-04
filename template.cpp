#include <bits/stdc++.h>

using namespace std;

// Be careful when using INF as sentinel in Graph Theory and Dynamic Programming problems. After you run your algorithm having
// a value lesser than INF doesn't always mean that a state is unreachable or invalid because we may have negative weights.

// Be careful when solving an inequation such as x >= a / b. To get ceil(a / b) use the code floor_ceil.cpp under "Number Theory" folder.

// Caution when constructing objects using brace-init-lists as this will also call the constructor if there's one with matching parameters.
// This means that Fraction f = {num, den} will behave the same way as Fraction f = Fraction(num, den).

// Trie is the most beautiful Data Structure. It is a more generic version of the Dynamic (Implicit) Segment Tree, since it doesn't need to be binary.
// The Trie can behave just like a Segment Tree if you insert the value a[i] at the node that represents position i (following the path given by the decomposition of i in binary).

// Use: s = regex_replace(s, regex(a), b); to replace every occurence of a for b in s.

// Maximum number of divisors for N <= 10^5 ---> 83160 with 128 divisors.
// Maximum number of divisors for N <= 10^6 ---> 720720 with 240 divisors.
// Maximum number of divisors for N <= 10^9 ---> 735134400 with 1344 divisors.
// Maximum number of divisors for N <= 10^18 ---> 897612484786617600 with 103680 divisors.

// How to generate random numbers and random permutations:
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng_64(chrono::steady_clock::now().time_since_epoch().count());
// int x = uniform_int_distribution<int>(l, r)(rng);
// long long x = uniform_int_distribution<long long>(l, r)(rng_64);
// double x = uniform_real_distribution<double>(l, r)(rng);
// shuffle(p.begin(), p.end(), rng);

constexpr double PI = 3.14159265358979323846;
constexpr int MOD = 1000000007;
constexpr int INF = 0x3f3f3f3f;
#define mp make_pair
#define pb push_back
#define fi first
#define se second

typedef long long ll;
typedef unsigned long long ull;

int main() {
	// ios::sync_with_stdio(false);

	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);

	return 0;
}
