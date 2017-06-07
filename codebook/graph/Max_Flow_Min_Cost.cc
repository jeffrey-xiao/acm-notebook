#include <bits/stdc++.h>
using namespace std;
struct Edge {
    int orig, dest, origCost, cost, flow, last;
    Edge (int orig, int dest, int cost, int flow, int last): orig(orig), dest(dest), origCost(cost), cost(cost), flow(flow), last(last) {}
};
struct Vertex {
    int index, cost;
    Vertex (int index, int cost): index(index), cost(cost) {}
    bool operator < (const Vertex& v) const {
        return cost < v.cost;
    }
};
struct MaxFlowMinCost {
    int N, src, sink, cnt = 0;
    vector<Edge> e;
    vector<int> last, phi, prev, dist, index;
    MaxFlowMinCost (int N, int src, int sink): N(N), src(src), sink(sink), last(N), phi(N), prev(N), dist(N), index(N) {
        fill(last.begin(), last.end(), -1);
    }

    void addEdge (int u, int v, int flow, int cost) {
        e.push_back({u, v, cost, flow, last[u]});
        last[u] = (int)e.size() - 1;
        e.push_back({v, u, -cost, 0, last[v]});
        last[v] = (int)e.size() - 1;
    }

    void reduceCost () {
        for (int i = 0; i < (int)e.size(); i += 2) {
            e[i].cost += phi[e[i].orig] - phi[e[i].dest];
            e[i ^ 1].cost = 0;
        }
    }

    void bellmanFord () {
        fill(phi.begin(), phi.end(), 1 << 25);
        phi[src] = 0;
        for (int j = 0; j < N - 1; j++)
            for (int i = 0; i < (int)e.size(); i++)
                if (e[i].flow > 0)
                    phi[e[i].dest] = min(phi[e[i].dest], phi[e[i].orig] + e[i].cost);
    }

    bool dijkstra () {
        fill(dist.begin(), dist.end(), 1 << 30);
        fill(prev.begin(), prev.end(), -1);
        fill(index.begin(), index.end(), -1);
        dist[src] = 0;
        priority_queue<Vertex> pq;
        pq.push({src, 0});
        while (!pq.empty()) {
            Vertex curr = pq.top();
            pq.pop();
            for (int next = last[curr.index]; next != -1; next = e[next].last) {
                if (e[next].flow == 0 || dist[e[next].dest] <= dist[curr.index] + e[next].cost)
                    continue;
                dist[e[next].dest] = dist[curr.index] + e[next].cost;
                prev[e[next].dest] = curr.index;
                index[e[next].dest] = next;
                pq.push({e[next].dest, dist[e[next].dest]});
            }
        }
        return dist[sink] != 1 << 30;
    }

    pair<int, int> getMaxFlowMinCost () {
        int flow = 0;
        int cost = 0;
        bellmanFord();
        reduceCost();
        while (dijkstra()) {
            for (int i = 0; i < N; i++)
                phi[i] = dist[i];
            reduceCost();
            int aug = 1 << 30;
            int curr = sink;
            while (prev[curr] != -1) {
                aug = min(aug, e[index[curr]].flow);
                curr = prev[curr];
            }
            flow += aug;
            curr = sink;
            while (prev[curr] != -1) {
                e[index[curr]].flow -= aug;
                e[index[curr] ^ 1].flow += aug;
                cost += aug * e[index[curr]].origCost;
                curr = prev[curr];
            }
        }
        return {flow, cost};
    }
};
