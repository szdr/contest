#include <string>
using namespace std;
typedef unsigned long long ULL;
const ULL B = 100000007;

int contain(string a, string b) {
    int res = 0;
    int al = a.length(), bl = b.length();
    if (al > bl) {
        return res;
    }

    // B^{al}
    ULL t = 1;
    for (int i = 0; i < al; i++) {
        t *= B;
    }

    // calculate hash value for a[:al] and b[:al]
    ULL ah = 0, bh = 0;
    for (int i = 0; i < al; i++) {
        ah = ah * B + a[i];
    }
    for (int i = 0; i < al; i++) {
        bh = bh * B + b[i];
    }

    // check hash value for b with sliding pointer of b
    for (int i = 0; i + al <= bl; i++) {
        if (ah == bh) {
            res += 1;
        }
        if (i + al < bl) {
            bh = bh * B + b[i+al] - b[i] * t;
        }
    }
    return res;
}
