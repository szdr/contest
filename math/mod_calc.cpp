typedef long long LL;
const int MOD = 1e9 + 7;

// a+b (mod p)
LL add_mod(int a, int b) {
    LL d = (a % MOD) + (b % MOD) % MOD;
    return d;
}

// a-b (mod p)
LL sub_mod(int a, int b) {
    LL d = (a % MOD - b % MOD + MOD) % MOD;
    return d;
}

// a*b (mod p)
LL mul_mod(int a, int b) {
    LL d = (a % MOD) * (b % MOD) % MOD;
    return d;
}

// a^b (mod p)
LL power_mod(int a, int b) {
    if (b == 0) {
        return 1;
    }
    if (b % 2 == 0) {
        LL d = power_mod(a, b / 2);
        return (d * d) % MOD;
    } else {
        return (a * power_mod(a, b - 1)) % MOD;
    }
}

// a \div b (mod p) CAUTION! p must be prime !
// By Fermat theorem, a^{p-1} \equiv 1 (mod p)
// so, a^{p-2} \equiv a^{-1} (mod p)
LL div_mod(int a, int b) {
    LL pos_p_2 = power_mod(b, MOD - 2);
    return (a * pos_p_2) % MOD;
}

const int MAX = 100;
LL fact[MAX];
void fact_mod(int n) {
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            fact[i] = 1;
        } else {
            fact[i] = fact[i-1] * i % MOD;
        }
    }
}

LL comb_mod(int n, int r) {
    LL res = fact[n];
    LL a = power_mod(fact[n - r], MOD - 2);
    LL b = power_mod(fact[r], MOD - 2);
    res = res * a % MOD;
    res = res * b % MOD;
    return res;
}
