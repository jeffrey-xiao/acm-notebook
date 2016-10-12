#include <bits/stdc++.h>
using namespace std;
int randomPriority () {
    return rand() * 65536 + rand();
}
struct Node {
    int val, p;
    Node *left, *right;
    Node (int val): val(val), p(randomPriority()) {
        left = nullptr;
        right = nullptr;
    }
};
struct Treap {
    Node* root;

    Treap () {
        root = nullptr;
    }

    // precondition: all values of u are smaller than all values of v
    Node* join (Node* u, Node* v) {
        if (u == nullptr)
            return v;
        if (v == nullptr)
            return u;
        if (u->p < v->p) {
            u->right = join(u->right, v);
            return u;
        }
        v->left = join(u, v->left);
        return v;
    }

    pair<Node*, Node*> split (Node* u, int k) {
        if (u == nullptr)
            return make_pair(nullptr, nullptr);
        if (u->val < k) {
            auto res = split(u->right, k);
            u->right = res.first;
            res.first = u;
            return res;
        } else if (u->val > k) {
            auto res = split(u->left, k);
            u->left = res.second;
            res.second = u;
            return res;
        } else {
            return make_pair(u->left, u->right);
        }
    }
    bool contains (int val) {
        return contains(root, val);
    }
    bool contains (Node* u, int val) {
        if (u == nullptr)
            return false;
        if (u->val < val)
            return contains(u->right, val);
        else if (u->val > val)
            return contains(u->left, val);
        return true;
    }
    void insert (int val) {
        if (contains(root, val))
            return;
        auto nodes = split(root, val);
        root = join(nodes.first, join(new Node(val), nodes.second));
    }
    void remove (int val) {
        if (root == nullptr)
            return;
        auto nodes = split(root, val);
        root = join(nodes.first, nodes.second);
    }
};
