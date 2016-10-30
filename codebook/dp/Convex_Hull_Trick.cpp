#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct ConvexHullTrick {
    vector<ll> M, B;
    int ptr = 0;

    void addLine (ll m, ll b) {
        int len = M.size();

        while (len > 1 && (B[len - 2] - B[len - 1]) * (m - M[len - 1]) >= (B[len - 1] - b) * (M[len - 1] - M[len - 2]))
            len--;
        M.resize(len);
        B.resize(len);
        M.push_back(m);
        B.push_back(b);
    }

    ll getMax (ll x) {
        if (ptr >= (int)M.size())
            ptr = (int)M.size() - 1;
        while (ptr < (int)M.size() - 1 && M[ptr + 1] * x + B[ptr + 1] >= M[ptr] * x + B[ptr])
            ptr++;
        return M[ptr] * x + B[ptr];
    }
};
