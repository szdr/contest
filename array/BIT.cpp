#include <vector>
#include <iostream>
using namespace std;

/*
 * Binary Indexed Tree
 * 次の操作をO(log n)で行う
 * 1) a_1 + a_2 + ... + a_n
 * 2) a_n += x
 *
 * Reference: 蟻本
 */
template <typename T>
struct BIT {
    int N;
    vector<T> bit;

    BIT (int N) {
        this -> N = N;
        for (int i = 0; i <= N; i++) {
            bit.push_back(0);
        }
    }

    /*
     * a_1 + a_2 + ... + a_n
     * O(log n)
     */
    T sum (int n) {
        T ret = 0;
        while (n > 0) {
            ret += bit[n];
            // nの最後の1のビットに対応する数を引く
            // ex) 0110 -> 0100 (= 0110 - 0010)
            n -= n & -n;
        }
        return ret;
    }

    /*
     * a_n += x
     * O(log n)
     */
    void add (int n, T x) {
        while (n <= N) {
            bit[n] += x;
            // nの最後の1のビットに対応する数を足す
            // ex) 0101 -> 0110 (= 0101 + 0001)
            n += n & -n;
        }
    }
};

int main(int argc, char const* argv[])
{
    int N = 8;
    BIT<int> bit(N);

    // A: 3, 2, 5, -3, 6, 1, 8, -2
    bit.add(1, 3);
    bit.add(2, 2);
    bit.add(3, 5);
    bit.add(4, -3);
    bit.add(5, 6);
    bit.add(6, 1);
    bit.add(7, 8);
    bit.add(8, -2);

    // a_1 + a_2 + a_3 = 3 + 2 + 5 = 10
    cout << "Expected: 10, Actual: " << bit.sum(3) << endl;
    // a_1 + a_2 + a_3 + a_4 = 3 + 2 + 5 - 3 = 7
    cout << "Expected: 7, Actual: " << bit.sum(4) << endl;
    // a_1 + a_2 + ... + a_8 = 3 + 2 + 5 - 3 + 6 + 1 + 8 - 2 = 20
    cout << "Expected: 20, Actual: " << bit.sum(8) << endl;
    return 0;
}
