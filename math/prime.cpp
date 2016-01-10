#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#define MAX_N 1000
typedef long long ll;
using namespace std;

// naive prime test
bool is_prime(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return n != 1;
}

// enumerate divided numbers
vector<int> divisor(int n) {
    vector<int> res;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);
            if (i != n / i) {
                res.push_back(n / i);
            }
        }
    }
    return res;
}

// prime factorization
map<int, int> prime_factor(int n) {
    map<int, int> res;
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            ++res[i];
            n /= i;
        }
    }
    if (n != 1) {
        res[n] = 1;
    }
    return res;
}

// Eratosthenes
int prime[MAX_N];
bool is_prime_list[MAX_N];

int sieve(int n) {
    int p = 0;
    fill(is_prime_list, is_prime_list + MAX_N, true);
    is_prime_list[0] = is_prime_list[1] = false;
    for (int i = 2; i <= n; i++) {
        if (is_prime_list[i]) {
            prime[p++] = i;
            for (int j = 2 * i; j <= n; j += i) {
                is_prime_list[j] = false;
            }
        }
    }
    return p;
}

// segment Eratosthenes sieve[a, b)
// is_prime_seg_list[i - a] = true means that i is prime
#define MAX_L 1000
#define MAX_SQRT_B 1000
bool is_prime_seg_list[MAX_L];
bool is_prime_small_list[MAX_SQRT_B];
void segment_sieve(ll a, ll b) {
    for (int i = 0; (ll)i * i < b; i++) {
        is_prime_small_list[i] = true;
    }
    for (int i = 0; i < b - a; i++) {
        is_prime_seg_list[i] = true;
    }
    for (int i = 2; (ll)i * i < b; i++) {
        if (is_prime_small_list[i]) {
            for (int j = 2 * i; (ll)j * j < b; j += i) {
                is_prime_small_list[j] = false;
            }
            for (ll j = max(2LL, (a + i - 1) / i) * i; j < b; j+= i) {
                is_prime_seg_list[j - a] = false;
            }
        }
    }
}
