#include <bits/stdc++.h>

using namespace std;

struct LinkCut {
    struct Node {
        int val;
        Node *child[2], *par;
        Node (int val): val(val) {
            child[0] = this;
            child[1] = this;
            par = this;
        }
    };

    static Node *null;
    Node *root;
    vector<Node*> nodes;

    LinkCut (int N): nodes(N) {}

    void access (Node* u) {

    }
};

LinkCut::Node* LinkCut::null = new Node(0);
