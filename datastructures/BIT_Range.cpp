#include <bits/stdc++.h>
using namespace std;
struct BIT_Range {
    int N;
    vector<int> val1, val2;
    BIT_Range (int N): N(N), val1(N), val2(N) {}

    void update (vector<int> &val, int idx, int v) {
        for (int x = idx; x < N; x += (x & -x))
            val[x] += v;
    }

    void update (int x1, int x2, int val) {
        update(val1, x1, val);
        update(val1, x2 + 1, -val);
        update(val2, x1, val * (x1 - 1));
        update(val2, x2 + 1, -val * x2);
    }

    int query (vector<int> &val, int idx) {
        int ret = 0;
        for (int x = idx; x > 0; x -= (x & -x))
            ret += val[x];
        return ret;
    }

    int query (int x) {
        return query(val1, x) * x - query(val2, x);
    }

    int query (int x1, int x2) {
        return query(x2) - query(x1 - 1);
    }
};
