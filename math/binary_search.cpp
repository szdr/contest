#include <iostream>
#include <vector>

using namespace std;

/*
 * Aはソート済み
 */
int get_max_index(vector<int> A, int key) {
    int N = A.size();
    // 区間は半開区間で持つ
    // [ok, ng)
    int ok = 0;
    int ng = N;
    while (abs(ok - ng) > 1) {
        int md = (ok + ng) / 2;
        if (A[md] <= key) {
            ok = md;
        } else {
            ng = md;
        }
    }
    return ok;
}

/*
 * Aはソート済み
 */
int get_min_index(vector<int> A, int key) {
    int N = A.size();
    // 区間は半開区間で持つ
    // (ng, ok]
    int ok = N - 1;
    int ng = -1;
    while (abs(ok - ng) > 1) {
        int md = (ok + ng) / 2;
        if (A[md] >= key) {
            ok = md;
        } else {
            ng = md;
        }
    }
    return ok;
}

int main(int argc, char const* argv[])
{
    vector<int> A = {1, 2, 3, 3, 4};
    cout << "Expected: 1" << endl;
    cout << "Actual: " << get_max_index(A, 2) << endl;

    cout << "Expected: 3" << endl;
    cout << "Actual: " << get_max_index(A, 3) << endl;

    cout << "Expected: 1" << endl;
    cout << "Actual: " << get_min_index(A, 2) << endl;

    cout << "Expected: 2" << endl;
    cout << "Actual: " << get_min_index(A, 3) << endl;
    return 0;
}
