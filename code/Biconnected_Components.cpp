#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> edge;
struct BiconnectedComponents {
    int N, cnt = 0;
    vector<edge> bridges;
    vector<vector<edge>> components;
    vector<vector<int>> adj;
    stack<edge> s;
    vector<int> lo, disc;
    vector<bool> vis, cutVertex;

    BiconnectedComponents (int N): N(N), adj(N), lo(N), disc(N), vis(N), cutVertex(N) {}

    void addEdge (int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs (int u, int prev) {
        disc[u] = lo[u] = cnt++;
        vis[u] = true;
        int children = 0;
        for (int v : adj[u]) {
            if (!vis[v]) {
                children++;
                s.push({u, v});
                dfs(v, u);
                lo[u] = min(lo[u], lo[v]);
                if ((disc[u] == 0 && children > 1) || (disc[u] > 0 && lo[v] >= disc[u])) {
                    cutVertex[u] = true;
                    components.push_back(vector<edge>());
                    while (s.top().first != u && s.top().second != v) {
                        components.back().push_back(edge(s.top().first, s.top().second));
                        s.pop();
                    }
                    components.back().push_back(edge(s.top().first, s.top().second));
                    s.pop();
                }
                if (lo[v] > disc[u])
                    bridges.push_back(edge(s.top().first, s.top().second));
            } else if (v != prev && disc[v] < lo[u]) {
                lo[u] = disc[v];
                s.push({u, v});
            }
        }
    }

    void compute () {
        for (int i = 0; i < N; i++)
            if (!vis[i])
                dfs(i, -1);
    }
};
