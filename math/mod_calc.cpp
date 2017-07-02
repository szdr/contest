#include<vector>
#include<iostream>
using namespace std;
typedef long long LL;

// a+b
LL add_mod(LL a, LL b, LL mod) {
    LL d = (a % mod) + (b % mod) % mod;
    return d;
}

// a-b
LL sub_mod(LL a, LL b, LL mod) {
    LL d = (a % mod - b % mod + mod) % mod;
    return d;
}

// a*b
LL mul_mod(LL a, LL b, LL mod) {
    LL d = (a % mod) * (b % mod) % mod;
    return d;
}

// (base)^p
LL power_mod(LL base, LL p, LL mod) {
    LL ans = 1;
    while (p > 0) {
        if (p % 2 == 1) {
            ans = (ans * base) % mod;
        }
        base = (base * base) % mod;
        p /= 2;
    }
    return ans;
}

// a \div b (mod p) CAUTION! p must be prime !
// By Fermat theorem, a^{p-1} \equiv 1 (mod p)
// so, a^{p-2} \equiv a^{-1} (mod p)
LL div_mod(LL a, LL b, LL mod) {
    LL pos_p_2 = power_mod(b, mod - 2, mod);
    return (a * pos_p_2) % mod;
}

vector<LL> fact_mod(int n, LL mod) {
    vector<LL> fact(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }

    return fact;
}

vector<LL> rfact_mod(int n, LL mod) {
    vector<LL> rfact(n + 1, 1);
    vector<LL> fact = fact_mod(n, mod);
    for (int i = 1; i <= n; i++) {
        rfact[i] = power_mod(fact[i], mod - 2, mod);
    }
    return rfact;
}

/*
 * WARNING: fact_modとrfact_modの事前計算が必要
 */
LL ncr_mod(LL n, LL r, vector<LL> fact, vector<LL> rfact, LL mod) {
    if (r > n || n < 0 || r < 0) {
        return 0;
    }
    LL ans = (fact[n] * rfact[r]) % mod;
    ans = (ans * rfact[n - r]) % mod;
    return ans;
}


int main(int argc, char const* argv[])
{
    const int MOD = 1e9 + 7;
    vector<LL> fact = fact_mod(100000, MOD);
    vector<LL> rfact = rfact_mod(100000, MOD);

    LL ans1 = ncr_mod(8, 4, fact, rfact, MOD);
    cout << "Expected: " << 70 << endl;
    cout << "Actual: " << ans1 << endl;

    LL ans2 = ncr_mod(50, 20, fact, rfact, MOD);
    cout << "Expected: " << 211914057 << endl;
    cout << "Actual: " << ans2 << endl;

    return 0;
}
