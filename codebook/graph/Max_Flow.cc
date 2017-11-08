/* Time: O(EV^2); O(min(V^(2/3), E^(1/2))E) for unit capacities
 * Memory: O(V + E)
 */

#include <bits/stdc++.h>

using namespace std;

struct Edge {
  int dest, cost, next;
  Edge (int dest, int cost, int next): dest(dest), cost(cost), next(next) {}
};

struct Network {
  int N, src, sink;
  vector<int> last, dist;
  vector<Edge> e;

  Network (int N, int src, int sink): N(N), src(src), sink(sink), last(N), dist(N) {
    fill(last.begin(), last.end(), -1);
  }

  void addEdge (int x, int y, int xy, int yx) {
    e.push_back(Edge(y, xy, last[x]));
    last[x] = (int)e.size() - 1;
    e.push_back(Edge(x, yx, last[y]));
    last[y] = (int)e.size() - 1;
  }

  bool getPath () {
    fill(dist.begin(), dist.end(), -1);
    queue<int> q;
    q.push(src);
    dist[src] = 0;

    while (!q.empty()) {
      int curr = q.front(); q.pop();
      for (int i = last[curr]; i != -1; i = e[i].next) {
        if (e[i].cost > 0 && dist[e[i].dest] == -1) {
          dist[e[i].dest] = dist[curr] + 1;
          q.push(e[i].dest);
        }
      }
    }

    return dist[sink] != -1;
  }

  int dfs (int curr, int flow) {
    if (curr == sink)
      return flow;
    int ret = 0;
    for (int i = last[curr]; i != -1; i = e[i].next) {
      if (e[i].cost > 0 && dist[e[i].dest] == dist[curr] + 1) {
        int res = dfs(e[i].dest, min(flow, e[i].cost));
        ret += res;
        e[i].cost -= res;
        e[i ^ 1].cost += res;
        flow -= res;
        if (flow == 0)
          break;
      }
    }
    return ret;
  }

  int getFlow () {
    int res = 0;
    while (getPath())
      res += dfs(src, 1 << 30);
    return res;
  }
};
