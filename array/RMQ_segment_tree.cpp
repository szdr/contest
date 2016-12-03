// 数列 {a_0, ..., a_{N-1}} に対して
// s,tが与えられたとき、a_s, ..., a_tの最小値を求める O(logN)
// k, xが与えられたとき、a_kの値をxにするO(logN)
#include <climits>
#include <algorithm>
using namespace std;
struct RMQ {
    const static int MAX_RMQ = 1 << 17;
    int n;
    int dat[2 * MAX_RMQ - 1];
    RMQ(int n_) {init(n_);}

    void init(int n_) {
        n = 1;
        while (n < n_) n *= 2;
        for (int i = 0; i < 2 * n - 1; i++) dat[i] = INT_MAX;
    }

    void update(int k, int x) {
        k += n - 1;
        dat[k] = x;
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }

    // [a, b)の最小値を求める
    // 呼び出しはquery(s, t, 0, 0, rmq.n)
    int query(int s, int t, int k, int l, int r) {
        if (r <= s || t <= l) return INT_MAX;

        if (s <= l && r <= t) {
            return dat[k];
        } else {
            int vl = query(s, t, k * 2 + 1, l, (l + r) / 2);
            int vr = query(s, t, k * 2 + 2, (l + r) / 2, r);
            return min(vl, vr);
        }

    }
};
