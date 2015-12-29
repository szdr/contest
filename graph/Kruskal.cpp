// Kruscal: minimum spanning tree
// O(E\log{V})
#include <algorithm>
using namespace std;

#define MAX_E 1000
#define MAX_V 1000

struct edge {int u, v, cost; };
edge  es[MAX_E];
int V, E;

// Kruscal uses union-find tree
int par[MAX_V];
int uf_rank[MAX_V];

void init_union_find(int v) {
    for (int i = 0; i < v; i++) {
        par[i] = i;
        uf_rank[i] = 0;
    }
}

int find(int x) {
    if (par[x] == x) {
        return x;
    } else {
        return par[x] = find(par[x]);
    }
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) {
        return;
    }
    if (uf_rank[x] < uf_rank[y]) {
        par[x] = y;
    } else {
        par[y] = x;
        if (uf_rank[x] == uf_rank[y]) {
            uf_rank[x]++;
        }
    }
}

bool same(int x, int y) {
    return find(x) == find(y);
}

bool comp(const edge& e1, const edge& e2) {
    return e1.cost < e2.cost;
}

int kruscal() {
    sort(es, es + E, comp);
    init_union_find(V);
    int res = 0;
    for (int i = 0; i < E; i++) {
        edge e = es[i];
        if (!same(e.u, e.v)) {
            unite(e.u, e.v);
            res += e.cost;
        }
    }
    return res;
}
