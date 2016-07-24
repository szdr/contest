typedef long long ll;

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
