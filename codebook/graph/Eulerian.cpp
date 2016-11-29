#include <bits/stdc++.h>
using namespace std;
struct Edge {
    int dest, index;
    bool used;
};
struct Euler {
    int N;
    vector<vector<Edge>> adj;
    vector<int> used;
    Euler (int N): N(N), adj(N), used(N) {}

    void addEdge (int u, int v) {
        adj[u].push_back({v, (int)adj[v].size(), 0});
        adj[v].push_back({u, (int)adj[u].size() - 1, 0});
    }

    // precondition: all vertices are connected
    int getEuler () {
        int odd = 0;
        for (int i = 0; i < N; i++)
            if ((int)adj[i].size() & 1)
                odd++;
        if (odd > 2)
            return -1;
        return odd == 0 ? 0 : 1;
    }

    bool isEulerianPath () {
        return getEuler() != -1;
    }

    bool isEulerianCycle () {
        return getEuler() == 0;
    }

    void printEulerianPath () {
        if (!isEulerianPath()) {
            printf("No Eulerian Path Exists.");
            return;
        }
        stack<int> order;
        int curr = 0;
        for (int i = 0; i < N; i++)
            if ((int)adj[i].size() & 1)
                curr = i;
        while (true) {
            if ((int)adj[curr].size() - used[curr] == 0) {
                printf("%d ", curr);
                if (order.size() == 0)
                    break;
                curr = order.top();
                order.pop();
            } else {
                order.push(curr);
                for (int i = 0; i < (int)adj[curr].size(); i++) {
                    if (!adj[curr][i].used) {
                        int dest = adj[curr][i].dest;
                        int index = adj[curr][i].index;
                        adj[curr][i].used = true;
                        adj[dest][index].used = true;
                        used[curr]++;
                        used[dest]++;
                        curr = dest;
                        break;
                    }
                }
            }
        }
    }
};
