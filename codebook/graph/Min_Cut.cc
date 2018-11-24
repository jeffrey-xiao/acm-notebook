/* Time: O(V^3)
 * Memory: O(V^2)
 */

#include <bits/stdc++.h>

using namespace std;

struct MinCut {
  int N;
  vector<vector<int>> adj;
  vector<int> weight;
  vector<bool> inContraction, used;
  MinCut(int N) : N(N), adj(N, vector<int>(N)), weight(N, 0), inContraction(N, 0), used(N, 0) {}

  void addEdge(int u, int v, int c) {
    adj[u][v] = c;
    adj[v][u] = c;
  }

  int getMinCut() {
    int minCut = 1 << 30;
    for (int v = N - 1; v >= 0; v--) {
      for (int i = 1; i < N; i++) {
        used[i] = inContraction[i];
        weight[i] = adj[0][i];
      }
      int prev = 0, curr = 0;
      for (int sz = 1; sz <= v; sz++) {
        prev = curr;
        curr = -1;
        for (int i = 1; i < N; i++)
          if (!used[i] && (curr == -1 || weight[i] > weight[curr]))
            curr = i;
        if (sz != v) {
          for (int i = 0; i < N; i++)
            weight[i] += adj[curr][i];
          used[curr] = true;
        } else {
          for (int i = 0; i < N; i++)
            adj[prev][i] = adj[i][prev] += adj[i][curr];
          inContraction[curr] = true;
          minCut = min(minCut, weight[curr]);
        }
      }
    }
    return minCut;
  }
};
