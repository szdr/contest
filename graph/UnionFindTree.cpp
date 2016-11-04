#include <vector>
using namespace std;
struct UnionFind {
    vector<int> par;
    int n, cnt;
    UnionFind(const int& x = 0) {init(x);}
    void init(const int& x) {par.assign(cnt=n=x, -1);}
    inline int find(const int& x) {return par[x] < 0 ? x : par[x] = find(par[x]);}
    inline bool same(const int& x, const int& y) { return find(x) == find(y); }
    inline bool unite(int x, int y) {
        if ((x = find(x)) == (y = find(y))) {
            return false;
        }
        --cnt;
        if (par[x] > par[y]) {
            swap(x, y);
        }
        par[x] += par[y];
        par[y] = x;
        return true;
    }
    inline int count() const {return cnt;}
    inline int count(int x) {return -par[find(x)];}
};
