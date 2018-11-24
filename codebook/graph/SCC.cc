/* Time: O(V)
 * Memory: O(V + E)
 */

#include <bits/stdc++.h>

using namespace std;

struct SCC {
  int N, cnt, idCnt;
  vector<int> disc, lo, id;
  vector<bool> inStack;
  vector<vector<int>> adj;
  stack<int> s;

  SCC(int N) : N(N), disc(N), lo(N), id(N), inStack(N), adj(N) {}

  void addEdge(int u, int v) {
    adj[u].push_back(v);
  }

  void dfs(int i) {
    disc[i] = lo[i] = ++cnt;
    inStack[i] = true;
    s.push(i);
    for (int j : adj[i]) {
      if (disc[j] == 0) {
        dfs(j);
        lo[i] = min(lo[i], lo[j]);
      } else if (inStack[j]) {
        lo[i] = min(lo[i], disc[j]);
      }
    }
    if (disc[i] == lo[i]) {
      while (s.top() != i) {
        inStack[s.top()] = false;
        id[s.top()] = idCnt;
        s.pop();
      }
      inStack[s.top()] = false;
      id[s.top()] = idCnt++;
      s.pop();
    }
  }

  void compute() {
    for (int i = 0; i < N; i++)
      if (disc[i] == 0)
        dfs(i);
  }
};
