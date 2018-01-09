/* O(log(max(a, b))). */
/* a * x + b * y = gcd(a, b) */
int extended_gcd(int a, int b, int &x, int &y){
    int x1, y1, gcd;

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

/* O(log(max(a, b))). */
/* a * x1 + b * y1 = c */
/* x = x1 - t * (b / gcd(a, b)) */
/* y = y1 + t * (a / gcd(a, b)) */
int diophantine(int a, int b, int c, int &x1, int &y1){
    int gcd, k, t;

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