#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <iostream>

using namespace std;

/*
 * 座標圧縮
 * input: (a_0, a_1, ..., a_{n-1})
 * output: {a_0: b_0, a_1: b_1, ..., a_{n-1}: b_{n-1}}
 * O(n log n)
 */
template <typename T>
map<T, int> zaatu (vector<T> arr) {
    int N = arr.size();
    map<T, int> ret;
    vector<T> arr_copy;
    copy(arr.begin(), arr.end(), back_inserter(arr_copy));
    sort(arr_copy.begin(), arr_copy.end());

    int compressed_index = 0;
    for (int i = 0; i < N; i++) {
        T e = arr_copy[i];
        if (i == 0) {
            ret[e] = compressed_index;
        } else {
            if (e != arr_copy[i-1]) {
                compressed_index += 1;
                ret[e] = compressed_index;
            }
        }
    }
    return ret;
}


int main(int argc, char const* argv[])
{
    // (4, 7, 9, 6, 12) -> (0, 2, 3, 1, 4)
    vector<int> A = {4, 7, 9, 6, 12};
    map<int, int> ret1 = zaatu(A);
    cout << "Expected: 0 2 3 1 4" << endl;
    cout << "Actual: ";
    for (auto e: A) {
        cout << ret1[e] << " ";
    }
    cout << endl;

    // (1, 3, 1, 2, 4) -> (0, 2, 0, 1, 3)
    A = {1, 3, 1, 2, 4};
    map<int, int> ret2 = zaatu(A);
    cout << "Expected: 0 2 0 1 3" << endl;
    cout << "Actual: ";
    for (auto e: A) {
        cout << ret2[e] << " ";
    }
    cout << endl;

    // (8, 3, 2, 3, 5) -> (3, 1, 0, 1, 2)
    A = {8, 3, 2, 3, 5};
    map<int, int> ret3 = zaatu(A);
    cout << "Expected: 3 1 0 1 2" << endl;
    cout << "Actual: ";
    for (auto e: A) {
        cout << ret3[e] << " ";
    }
    cout << endl;


    // (3, 3, 3, 3) -> (0, 0, 0, 0)
    A = {3, 3, 3, 3};
    map<int, int> ret4 = zaatu(A);
    cout << "Expected: 0 0 0 0" << endl;
    cout << "Actual: ";
    for (auto e: A) {
        cout << ret4[e] << " ";
    }
    cout << endl;

    // (3, 4, 3, 4) -> (0, 1, 0, 1)
    A = {3, 4, 3, 4};
    map<int, int> ret5 = zaatu(A);
    cout << "Expected: 0 1 0 1" << endl;
    cout << "Actual: ";
    for (auto e: A) {
        cout << ret5[e] << " ";
    }
    cout << endl;

    // (5, 1, 1, 1) -> (1, 0, 0, 0)
    A = {5, 1, 1, 1};
    map<int, int> ret6 = zaatu(A);
    cout << "Expected: 1 0 0 0" << endl;
    cout << "Actual: ";
    for (auto e: A) {
        cout << ret6[e] << " ";
    }
    cout << endl;
    return 0;
}
