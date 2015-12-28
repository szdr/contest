#include <iostream>
#include <vector>
using namespace std;
#define MAX_V 1000

vector<int> G[MAX_V];

/*
 * if edges have cost
struct edge {int to, cost; };
vector<edge> G[MAX_V];
*/

int main(int argc, char const* argv[])
{
    int V, E;
    cin >> V >> E;
    for (int i = 0; i < E; i++) {
        // append edge from s to t
        int s, t;
        cin >> s >> t;
        G[s].push_back(t);
        // G[t].push_back(s); if undirected graph
    }
    return 0;
}
