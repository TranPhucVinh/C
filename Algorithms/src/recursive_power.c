double myPow(double x, int n) {
    if (x == 1) return 1;

    if ( (x == -1) && (n > 0) ) return -1;
    if ( (x == -1) && (n < 0) ) return 1;

    if ( (n == INT_MIN) && (x >= 2) ) return 0;
    if ( (n == INT_MIN) && (1 < x < 2) ) return 1/myPow(x, INT_MAX);

    if (n > 0) {
        if (n == 1) return x;

        double half = myPow(x, n / 2);
        if (n % 2 == 0) {
            return half * half;
        } else {
            return half * half * x;
        }
    }
    if (n < 0) return 1/myPow(x, -n);

    return 1;
}
