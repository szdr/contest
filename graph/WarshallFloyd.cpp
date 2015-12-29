// WarchallFloyd: All-pairs shortest path

#include <algorithm>
using namespace std;

#define MAX_V 1000
int d[MAX_V][MAX_V]; // d[u][v]: cost from u to v
                     // d[u][v] = 0 if u == v
                     // d[u][v] = INF if edge from u to v doesn't exist
int V;

void warshall_floyd() {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}
