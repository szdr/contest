#include <algorithm>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

#define MAX_V 1000000
typedef int DistanceT;
const DistanceT DIST_INF = numeric_limits<DistanceT>::max() / 2;
struct edge {int to; DistanceT cost; };
typedef pair<DistanceT, int> P; // (minimum distance, vertex id)

vector<edge> G[MAX_V];
DistanceT d[MAX_V];

// O((|V|+|E|)log|V|)
void dijkstra(int s) {
    priority_queue<P, vector<P>, greater<P> > que;
    fill(d, d + MAX_V, DIST_INF);
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
            edge e = G[v][i];
            // relax
            if (d[e.to] > d[v] + e.cost) {
                d[e.to] = d[v] + e.cost;
                que.push(P(d[e.to], e.to));
            }
        }
    }
}
