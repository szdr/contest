#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int MAX_N = 100;
const int MAX_K = 100;
const int INF = numeric_limits<int>::max() / 2;
struct edge {int to, cap, rev;};
vector<edge> G[MAX_N];
bool used[MAX_N];
int N, K;

void add_edge(int from, int to, int cap) {
    G[from].push_back((edge){to, cap, (int)G[to].size()});
    G[to].push_back((edge){from, 0, (int)G[from].size() - 1});
}

int dfs(int v, int t, int f) {
    if (v == t) {
        return f;
    }
    used[v] = true;
    for (int i = 0; i < G[v].size(); i++) {
        edge &e = G[v][i];
        if (!used[e.to] and e.cap > 0) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int flow = 0;
    while (true) {
        fill(used, used + sizeof(used), 0);
        int f = dfs(s, t, INF);
        if (f == 0) {
            return flow;
        }
        flow += f;
    }
}

bool can[MAX_N][MAX_K];  // can[i][j]: i <-> j

void solve() {
    int s = N + K, t = s + 1;
    for (int i = 0; i < N; i++) {
        add_edge(s, i, 1);
    }
    for (int i = 0; i < K; i++) {
        add_edge(N + i, t, 1);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            if (can[i][j]) {
                add_edge(i, N + j, 1);
            }
        }
    }
    cout << max_flow(s, t) << endl;
}
