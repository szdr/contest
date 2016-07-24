typedef long long ll;

// n! (mod p)
ll fact_mod(int n, int p) {
    for (ll i = n - 1; i > 1; i--) {
        n = n * i % p;
    }
    return n;
}
