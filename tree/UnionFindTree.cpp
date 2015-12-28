#define MAX_N 1000
int par[MAX_N]; // parent
int rank[MAX_N]; // depth

// initialize with n elements
void init(int n) {
    for (int i = 0; i < n; i++) {
        par[i] = i;
        rank[i] = 0;
    }
}


// find the root of tree
int find(int x) {
    if (par[x] == x) {
        return x;
    } else {
        return par[x] = find(par[x]);
    }
}


// unite two sets
// a set contains x and the other set contains y
void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) {
        return;
    }
    if (rank[x] < rank[y]) {
        par[x] = y;
    } else {
        par[y] = x;
        if (rank[x] == rank[y]) {
            rank[x]++;
        }
    }
}

// whether x and y are included in the same set
bool same(int x, int y) {
    return find(x) == find(y);
}
