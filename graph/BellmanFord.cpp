#include <climits>
#include <string>
#define MAX_E 1000
#define MAX_V 1000
#define INF INT_MAX/3
// from - (cost) - to
struct edge {int from, to, cost; };
edge es[MAX_E];
int d[MAX_V]; // minimum distance
int V, E;

// find minimum distance from s to the others
void shortest_path(int s) {
    for (int i = 0; i < V; i++) {
        d[i] = INF;
    }
    d[s] = 0;
    while (true) {
        bool update = false;
        for (int i = 0; i < E; i++) {
            edge e = es[i];
            if (d[e.from] != INF and d[e.to] > d[e.from] + e.cost) {
                d[e.to] = d[e.from] + e.cost;
                update = true;
            }
        }
        if (!update) {
            break;
        }
    }
}

// whether negative loop exists or not
bool find_negative_loop() {
    memset(d, 0, sizeof(d));
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < E; j++) {
            edge e = es[j];
            if (d[e.to] > d[e.from] + e.cost) {
                d[e.to] = d[e.from] + e.cost;
                if (i == V - 1) {
                    return true;
                }
            }
        }
    }
    return false;
}

