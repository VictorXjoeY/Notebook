/* Every individual fraction has to have a numerator and a denominator lesser than these mods.
   The time complexity of the division and construction can be exchanged by the time complexity of the == comparison operator. */
long long m[2] = {1000000007, 1000000009};
 
/* O(Log(Y)). */
long long fast_exp(long long x, long long y, long long m){
	long long ans = 1; // Base case.
 
	// In case x >= m.
	x %= m;
 
	// Decomposing y in binary. Multiplying the answer by x^1, x^2, x^4, x^8, ...
	while (y > 0){
		// If current bit is set.
		if (y & 1ll){
			ans = (ans * x) % m;
		}
 
		y >>= 1ll; // Next bit.
		x = (x * x) % m; // Next power of x.
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
