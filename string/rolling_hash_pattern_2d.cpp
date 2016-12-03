/*
 * AOJ 1_14_C
 */
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <utility>
#include <set>
#include <list>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <iterator> 
#include <limits>

#define REP(i,n) for (int i=0;i<(n);i++)
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define ALL(a) (a).begin(),(a).end()
#define RALL(A) (a).rbegin(),(a).rend()
#define PB push_back
#define MP make_pair

#define dump(x) cerr << #x << " = " << (x) << endl;

using namespace std;
const double PI = 3.14159265358979323846;
const double EPS = 1e-12;
const int INF = numeric_limits<int>::max() / 2;
const int NEG_INF = numeric_limits<int>::min() / 2;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef long long LL;
typedef unsigned long long ULL;
const ULL B = 100000007;
int H, W;
int R, C;
const int MAX_SIZE = 2000;
char table[MAX_SIZE][MAX_SIZE];
char query[MAX_SIZE][MAX_SIZE];

ULL res_hash[MAX_SIZE][MAX_SIZE], tmp[MAX_SIZE][MAX_SIZE];

// compute hash a[:R, :C]
void compute_hash(char a[MAX_SIZE][MAX_SIZE], int n, int m) {
    const ULL B1 = 9973;
    const ULL B2 = 100000007;
    ULL t1 = 1;
    for (int j = 0; j < C; j++) {
        t1 *= B1;
    }
    for (int i = 0; i < n; i++) {
        ULL e = 0;
        for (int j = 0; j < C; j++) {
            e = e * B1 + a[i][j];
        }
        for (int j = 0; j + C <= m; j++) {
            tmp[i][j] = e;
            if (j + C < m) {
                e = e * B1 - t1 * a[i][j] + a[i][j+C];
            }
        }
    }
    ULL t2 = 1;
    for (int i = 0; i < R; i++) {
        t2 *= B2;
    }
    for (int j = 0; j + C <= m; j++) {
        ULL e = 0;
        for (int i = 0; i < R; i++) {
            e = e * B2 + tmp[i][j];
        }
        for (int i = 0; i + R <= n; i++) {
            res_hash[i][j] = e;
            if (i + R < n) {
                e = e * B2 - t2 * tmp[i][j] + tmp[i+R][j];
            }
        }
    }

}



int main(int argc, char const* argv[])
{
    cin >> H >> W;
    REP(i, H) {
        REP(j, W) {
            cin >> table[i][j];
        }
    }
    cin >> R >> C;
    REP(i, R) {
        REP(j, C) {
            cin >> query[i][j];
        }
    }
    compute_hash(query, R, C);
    ULL query_hash = res_hash[0][0];
    compute_hash(table, H, W);
    for (int i = 0; i + R <= H; i++) {
        for (int j = 0; j + C <= W; j++) {
            if (res_hash[i][j] == query_hash) {
                cout << i << " " << j << endl;
            }
        }
    }

    return 0;
}
