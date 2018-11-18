/* O(log(max(a, b))). */
/* a * x + b * y = gcd(a, b) */
long long extended_gcd(long long a, long long b, long long &x, long long &y){
    long long x1, y1, gcd;

    if (a == 0){
        x = 0;
        y = 1;
        return b;
    }
 
    gcd = extended_gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
 
    return gcd;
}

/* O(log(max(a, b))).
a * x + b * y = c
    x = x1 + k * (b / gcd(a, b))
    y = y1 - k * (a / gcd(a, b))

a * x - b * y = c ---> a * x + b * (-y) = c
    x = x1 + k * (b / gcd(a, b))
    -y = y1 - k * (a / gcd(a, b)) ---> y = -y1 + k * (a / gcd(a, b))

-a * x + b * y = c ---> a * (-x) + b * y = c
    -x = x1 + k * (b / gcd(a, b)) ---> x = -x1 - k * (b / gcd(a, b))
    y = y1 - k * (a / gcd(a, b))

-a * x - b * y = c ---> a * (-x) + b * (-y) = c
    -x = x1 + k * (b / gcd(a, b)) ---> x = -x1 - k * (b / gcd(a, b))
    -y = y1 - k * (a / gcd(a, b)) ---> y = -y1 + k * (a / gcd(a, b))
    
Has a solution if and only if gcd(a, b) divides c. GCD will be positive if a and b are positive. */
long long diophantine(long long a, long long b, long long c, long long &x1, long long &y1){
    long long gcd, k, t;

    // Obtaining a * x1 + b * y1 = gcd(a, b)
    gcd = extended_gcd(a, b, x1, y1);

    // No solution
    if (c % gcd != 0){
        return 0;
    }

    // Multiplying the above equation by k = c / gcd we have a * x1 + b * y1 = c
    k = c / gcd;
    x1 *= k;
    y1 *= k;

    // Simplifying the solution so that x1 is minimum and positive
    t = x1 / (b / gcd);
    x1 -= t * (b / gcd);
    y1 += t * (a / gcd);

    if (x1 < 0){
        t = x1 - (b / gcd) > 0 ? 1 : -1;
        x1 -= t * (b / gcd);
        y1 += t * (a / gcd);
    }

    return gcd;
}