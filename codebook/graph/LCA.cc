#include <bits/stdc++.h>
using namespace std;
struct LCA {
    int N, LN;
    vector<int> depth;
    vector<vector<int>> pa;
    vector<vector<int>> adj;
    LCA (int N): N(N), LN(ceil(log(N) / log(2) + 1)), depth(N), pa(N, vector<int>(LN)), adj(N) {
        for (auto &x : pa)
            fill(x.begin(), x.end(), -1);
    }

    void addEdge (int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs (int u, int d, int prev) {
        depth[u] = d;
        pa[u][0] = prev;
        for (int v : adj[u])
            if (v != prev)
                dfs(v, d + 1, u);
    }

    void precompute () {
        for (int i = 1; i < LN; i++)
            for (int j = 0; j < N; j++)
                if (pa[j][i - 1] != -1)
                    pa[j][i] = pa[pa[j][i - 1]][i - 1];

    }

    int getLca (int u, int v) {
        if (depth[u] < depth[v])
            swap(u, v);
        for (int k = LN - 1; k >= 0; k--)
            if (pa[u][k] != -1 && depth[pa[u][k]] >= depth[v])
                u = pa[u][k];
        if (u == v)
            return u;
        for (int k = LN - 1; k >= 0; k--)
            if (pa[u][k] != -1 && pa[v][k] != -1 && pa[u][k] != pa[v][k])
                u = pa[u][k], v = pa[v][k];
        return pa[u][0];
    }
};
