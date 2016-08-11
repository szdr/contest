typedef long long ll;

// a+b (mod p)
ll add_mod(int a, int b, int p) {
    ll d = a + b;
    return d % p;
}

// a-b (mod p)
ll sub_mod(int a, int b, int p) {
    ll d = a + p;
    d -= b;
    return d % p;
}

// a*b (mod p)
ll mul_mod(int a, int b, int p) {
    ll d = (a % p) * (b % p);
    return d;
}

// a^b (mod p)
ll power_mod(int a, int b, int p) {
    if (b == 0) {
        return 1;
    }
    if (b % 2 == 0) {
        ll d = power_mod(a, b / 2, p);
        return (d * d) % p;
    } else {
        return (a * power_mod(a, b - 1, p)) % p;
    }
}

// a \div b (mod p) CAUTION! p must be prime !
// By Fermat theorem, a^{p-1} \equiv 1 (mod p)
// so, a^{p-2} \equiv a^{-1} (mod p)
ll div_mod(int a, int b, int p) {
    ll pos_p_2 = power_mod(b, p - 2, p);
    return (a * pos_p_2) % p;
}
