#include <iostream>
#include <vector>
#include <queue>

#define REP(i,n) for (int i=0;i<(n);i++)

using namespace std;

const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;
const int MAX = 10000;
int color[MAX];
int indeg[MAX];
vector<int> G[MAX];
int n;
int e;

queue<int> que;
vector<int> ans;

void bfs(int s) {
    que.push(s);
    color[s] = GRAY;
    while (!que.empty()) {
        int u = que.front(); que.pop();
        ans.push_back(u);
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
    REP(s, n) {
        for (auto it = G[s].begin(); it != G[s].end(); it++) {
            indeg[*it] += 1;
        }
    }
    REP(u, n) {
        if (indeg[u] == 0 and color[u] == WHITE) {
            bfs(u);
        }
    }
}
