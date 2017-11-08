/* Time: O(log N) query; O(N) construction
 * Memory: O(N)
 */

#include <bits/stdc++.h>

using namespace std;

struct HLD {
  int N, chainIndex;
  vector<vector<int>> adj;
  vector<int> sz, depth, chain, par, head;

  HLD (int N): N(N), adj(N), sz(N), depth(N), chain(N), par(N), head(N) {
    fill(head.begin(), head.end(), -1);
  }

  void addEdge (int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void dfs (int u, int p, int d) {
    par[u] = p;
    depth[u] = d;
    sz[u] = 1;
    for (int v : adj[u]) {
      if (v != p) {
        dfs(v, u, d + 1);
        sz[u] += sz[v];
      }
    }
  }

  void build (int u, int p) {
    if (head[chainIndex] == -1)
      head[chainIndex] = u;
    chain[u] = chainIndex;

    int maxIndex = -1;
    for (int v : adj[u])
      if (v != p && (maxIndex == -1 || sz[v] > sz[maxIndex]))
        maxIndex = v;
    if (maxIndex != -1)
      build(maxIndex, u);
    for (int v : adj[u])
      if (v != p && v != maxIndex) {
        chainIndex++;
        build(v, u);
      }
  }

  void precompute () {
    dfs(0, -1, 0);
    build(0, -1);
  }

  int getLca (int u, int v) {
    while (chain[u] != chain[v]) {
      if (depth[head[chain[u]]] < depth[head[chain[v]]])
        v = par[head[chain[v]]];
      else
        u = par[head[chain[u]]];
    }
    return depth[u] < depth[v] ? u : v;
  }
};
