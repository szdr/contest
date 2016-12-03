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

int text_size, k = 1;
const int MAX_N = 2000000;
int sa[MAX_N];
int sarank[MAX_N];
int tmp[MAX_N];
string T, P;
int Q;

// compare (rank[i], rank[i+k]) and (rank[j], rank[j+k])
bool compare_sa(int i, int j) {
    if (sarank[i] != sarank[j]) {
        return sarank[i] < sarank[j];
    } else {
        int ri = (i + k <= text_size ? sarank[i+k] : -1);
        int rj = (j + k <= text_size ? sarank[j+k] : -1);
        return ri < rj;
    }
}

// construct suffix array
void construct_sa(string S) {
    text_size = S.size();
    for (int i = 0; i <= text_size; i++) {
        sa[i] = i;
        sarank[i] = (i < text_size ? S[i] : -1);
    }
    // k文字についてソートされているところから、2k文字でソートする
    for (; k <= text_size; k *= 2) {
        sort(sa, sa + text_size + 1, compare_sa);

        // いったんtmpに次のランクを計算し、それからrankに移す
        tmp[sa[0]] = 0;
        for (int i = 1; i <= text_size; i++) {
            tmp[sa[i]] = tmp[sa[i-1]] + (compare_sa(sa[i-1], sa[i]) ? 1 : 0);
        }
        for (int i = 0; i <= text_size; i++) {
            sarank[i] = tmp[i];
        }
    }
}

bool contain(string S, string T) {
    int l = 0, r = S.size();
    while (l <= r) {
        int m = (l + r) / 2;
        // Sのsa[c]文字目から|T|文字とTを比較
        if (S.compare(sa[m], T.size(), T) < 0) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return (S.compare(sa[r+1], T.size(), T) == 0);
}

int main(int argc, char const* argv[])
{
    cin >> T;
    cin >> Q;
    construct_sa(T);
    REP(i, Q) {
        cin >> P;
        if (contain(T, P)) {
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
        }
    }
    return 0;
}
