#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;
const int INF = numeric_limits<int>::max() / 2;
const int MAX_N = 10000;
const int MAX_BUCKET = 100;
int A[MAX_N];
int B[MAX_BUCKET];
int N, Q;

void init() {
    int b = floor(sqrt(N));
    int i = 0;
    int ib = 0;
    while (i < N) {
        int tmp = INF;
        for (int j = i; j < min(i + b, N); j++) {
            tmp = min(tmp, A[j]);
        }
        B[ib] = tmp;
        i += b;
        ib += 1;
    }
}

// [s, t]
int min_query(int s, int t) {
    int b = floor(sqrt(N));
    int res = INF;
    int i = 0;
    int ib = 0;
    while (i < N) {
        int j = min(i + b - 1, N - 1);
        // 完全に含まれている
        if (s <= i and j <= t) {
            res = min(res, B[ib]);
        // クエリの左端がはみ出している
        } else if (i < s and j <= t) {
            for (int k = s; k <= j; k++) {
                res = min(res, A[k]);
            }
        // クエリの右端がはみ出している
        } else if (i <= t and t < j) {
            for (int k = i; k <= t; k++) {
                res = min(res, A[k]);
            }
        }
        i += b;
        ib += 1;
    }
    return res;
}

// [s, t]
void update(int i, int x) {
    A[i] = x;
    init();
}
