const int MAX_N = 1000;
int bit[MAX_N + 1], n;

int sum(int i) {
    int s = 0;
    while (i > 0) {
        s += bit[i];
        i -= i & -i; // iの最後の1のビットに対応する数を引く ex) 0110 -> 0100
    }
    return s;
}

void add(int i, int x) {
    while (i <= n) {
        bit[i] += x;
        i += i & -i; // iの最後の1のビットに対応する数を足す ex) 0101 -> 0110
    }
}
