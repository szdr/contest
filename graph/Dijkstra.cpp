#include <climits>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define MAX_V 1000
#define INF INT_MAX/3
struct edge {int to, cost; };
typedef pair<int, int> P; // (minimum distance, vertex id)

int V;
vector<edge> G[MAX_V];
int d[MAX_V];

void dijkstra(int s) {
    priority_queue<P, vector<P>, greater<P> > que;
    fill(d, d + V, INF);
    d[s] = 0;
    que.push(P(0, s));

    while (!que.empty()) {
        P p = que.top(); que.pop();
        int v = p.second;
        // can't 'relax
        if (d[v] < p.first) {
            continue;
        }
        for (int i = 0; i < G[v].size(); i++) {
            edge e = G[V][i];
            // relax
            if (d[e.to] > d[v] + e.cost) {
                d[e.to] = d[v] + e.cost;
                que.push(P(d[e.to], e.to));
            }
        }
    }
}
