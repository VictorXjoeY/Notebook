/* The time complexity of the division and construction can be exchanged by the time
complexity of the == comparison operator by storing both p and q modulo m instead of
just storing x = p * q^(-1) modulo m. */

// Every individual fraction has to have a numerator and a denominator lesser than these mods.
constexpr long long m[2] = {1000000007, 1000000009};
 
/* O(Log(B)). */
long long fast_exp(long long a, long long b, long long m){
	long long ans = 1; // Base case.

	// In case a >= m.
	a %= m;

	// Decomposing b in binary. Multiplying the answer by a^1, a^2, a^4, a^8, ...
	while (b > 0){
		// If current bit is set.
		if (b & 1ll){
			ans = (ans * a) % m;
		}

		b >>= 1ll; // Next bit.
		a = (a * a) % m; // Next power of a.
	}

	return ans;
}

struct Fraction{
	long long x[2]; // Stores x = p * q^(-1) (mod m) with x >= 0
 
 	/* O(1). */
	Fraction(){
		memset(this->x, 0, sizeof(this->x));
	}
 
 	/* O(Log(M)). */
	Fraction(long long p, long long q){
		for (int k = 0; k < 2; k++){
			this->x[k] = ((p * fast_exp(q, m[k] - 2, m[k])) % m[k] + m[k]) % m[k];
		}
	}
 
 	/* O(1) - Fraction addition. */
	Fraction operator + (const Fraction &f) const{
		Fraction ans;
 
		for (int k = 0; k < 2; k++){
			ans.x[k] = (this->x[k] + f.x[k]) % m[k];
		}
 
		return ans;
	}
 
 	/* O(1) - Fraction subtraction. */
	Fraction operator - (const Fraction &f) const{
		Fraction ans;
 
		for (int k = 0; k < 2; k++){
			ans.x[k] = ((this->x[k] - f.x[k]) % m[k] + m[k]) % m[k];
		}
 
		return ans;
	}
 
 	/* O(1) - Fraction multiplication. */
	Fraction operator * (const Fraction &f) const{
		Fraction ans;
 
		for (int k = 0; k < 2; k++){
			ans.x[k] = (this->x[k] * f.x[k]) % m[k];
		}
 
		return ans;
	}
 
 	/* O(Log(M)) - Fraction division. */
	Fraction operator / (const Fraction &f) const{
		Fraction ans;
 
		for (int k = 0; k < 2; k++){
			ans.x[k] = (this->x[k] * fast_exp(f.x[k], m[k] - 2, m[k])) % m[k];
		}
 
		return ans;
	}
 
 	/* O(1) - Checks if two fraction are equal based on their hash values. */
	bool operator == (const Fraction &f) const{
		for (int k = 0; k < 2; k++){
			if (this->x[k] != f.x[k]){
				return false;
			}
		}
 
		return true;
	}

 	/* O(1) - Checks if two fraction are not equal based on their hash values. */
 	bool operator != (const Fraction &f) const{
 		return !((*this) == f);
 	}
};
