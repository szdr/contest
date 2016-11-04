#include <iostream>
#include <vector>
#include <queue>

#define REP(i,n) for (int i=0;i<(n);i++)

using namespace std;

const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;
const int MAX_N = 10000;
int color[MAX_N];
int indeg[MAX_N];
vector<int> G[MAX_N];
int N;

queue<int> que;
vector<int> topo;

void bfs(int s) {
    que.push(s);
    color[s] = GRAY;
    while (!que.empty()) {
        int u = que.front(); que.pop();
        topo.push_back(u);
        for (auto it = G[u].begin(); it != G[u].end(); it++) {
            indeg[*it]--;
            if (indeg[*it] == 0 and color[*it] == WHITE) {
                color[*it] = GRAY;
                que.push(*it);
            }
        }
    }
}

void topological_sort() {
    REP(s, N) {
        for (auto it = G[s].begin(); it != G[s].end(); it++) {
            indeg[*it] += 1;
        }
    }
    REP(u, N) {
        if (indeg[u] == 0 and color[u] == WHITE) {
            bfs(u);
        }
    }
}
