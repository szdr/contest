typedef long long LL;

// a+b (mod p)
LL add_mod(int a, int b, int p) {
    LL d = (a % p) + (b % p);
    return d % p;
}

// a-b (mod p)
LL sub_mod(int a, int b, int p) {
    LL d = (a % p) - (b % p);
    return d % p;
}

// a*b (mod p)
LL mul_mod(int a, int b, int p) {
    LL d = (a % p) * (b % p);
    return d % p;
}

// a^b (mod p)
LL power_mod(int a, int b, int p) {
    if (b == 0) {
        return 1;
    }
    if (b % 2 == 0) {
        LL d = power_mod(a, b / 2, p);
        return (d * d) % p;
    } else {
        return (a * power_mod(a, b - 1, p)) % p;
    }
}

// a \div b (mod p) CAUTION! p must be prime !
// By Fermat theorem, a^{p-1} \equiv 1 (mod p)
// so, a^{p-2} \equiv a^{-1} (mod p)
LL div_mod(int a, int b, int p) {
    LL pos_p_2 = power_mod(b, p - 2, p);
    return (a * pos_p_2) % p;
}

const int MAX = 100;
LL fact[MAX];
void fact_mod(int n, int p) {
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            fact[i] = 1;
        } else {
            fact[i] = fact[i-1] * i % p;
        }
    }
}

LL comb_mod(int n, int r, int p) {
    LL res = fact[n];
    LL a = power_mod(fact[n - r], p - 2, p);
    LL b = power_mod(fact[r], p - 2, p);
    res = res * a % p;
    res = res * b % p;
    return res;
}
