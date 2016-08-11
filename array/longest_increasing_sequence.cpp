#include <algorithm>
const int N = 100;
const int INF = (1 << 30);
int A[N];
int dp[N];

using namespace std;

int longest_increasing_sequence() {
    for (int i = 0; i < N; i++) {
        dp[i] = INF;
    }
    for (int i = 0; i < N; i++) {
        int ind = distance(dp, lower_bound(dp, dp + N, A[i]));
        dp[ind] = A[i];
    }
    int res = distance(dp, lower_bound(dp, dp + N, INF));
    return res;
}
