/* We just have to guarantee that the denominator will not be a multiple of these mods at any moment. */
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
	long long p[2], q[2];
 
 	/* O(1). */
	Fraction(){
		for (int k = 0; k < 2; k++){
			this->p[k] = 0;
			this->q[k] = 1;
		}
	}
 
 	/* O(1). */
	Fraction(long long p, long long q){
		for (int k = 0; k < 2; k++){
			this->p[k] = p % m[k];
			this->q[k] = q % m[k];
		}
	}
 
 	/* O(1) - Fraction addition. */
	Fraction operator + (const Fraction &f) const{
		Fraction ans;
 
		for (int k = 0; k < 2; k++){
			ans.p[k] = (this->p[k] * f.q[k] + f.p[k] * this->q[k]) % m[k];
			ans.q[k] = (this->q[k] * f.q[k]) % m[k];
		}
 
		return ans;
	}
 
 	/* O(1) - Fraction subtraction. */
	Fraction operator - (const Fraction &f) const{
		Fraction ans;
 
		for (int k = 0; k < 2; k++){
			ans.p[k] = (this->p[k] * f.q[k] - f.p[k] * this->q[k]) % m[k];
			ans.q[k] = (this->q[k] * f.q[k]) % m[k];
		}
 
		return ans;
	}
 
 	/* O(1) - Fraction multiplication. */
	Fraction operator * (const Fraction &f) const{
		Fraction ans;
 
		for (int k = 0; k < 2; k++){
			ans.p[k] = (this->p[k] * f.p[k]) % m[k];
			ans.q[k] = (this->q[k] * f.q[k]) % m[k];
		}
 
		return ans;
	}
 
 	/* O(1) - Fraction division. */
	Fraction operator / (const Fraction &f) const{
		Fraction ans;
 
		for (int k = 0; k < 2; k++){
			ans.p[k] = (this->p[k] * f.q[k]) % m[k];
			ans.q[k] = (this->q[k] * f.p[k]) % m[k];
		}
 
		return ans;
	}
 	
 	/* O(Log(M)) - Returns x = p * q^-1 (mod m). */
	long long x(int k) const{
		return ((this->p[k] * fast_exp(this->q[k], m[k] - 2, m[k])) % m[k] + m[k]) % m[k];
	}
 
 	/* O(Log(M)) - Checks if two fraction are equal based on their hash values. */
	bool operator == (const Fraction &f) const{
		for (int k = 0; k < 2; k++){
			if (this->x(k) != f.x(k)){
				return false;
			}
		}
 
		return true;
	}

 	/* O(Log(M)) - Checks if two fraction are not equal based on their hash values. */
 	bool operator != (const Fraction &f) const{
 		return !((*this) == f);
 	}
};