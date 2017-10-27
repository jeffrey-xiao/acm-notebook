#include <bits/stdc++.h>
using namespace std;

struct Treap {
    struct Node {
        int val, p;
        Node *left, *right;
        Node (int val): val(val), p(randomPriority()) {
            left = nullptr;
            right = nullptr;
        }
    };

    static int randomPriority () {
        return rand() * 65536 + rand();
    }

    Node* root;

    Treap (): root(nullptr) {}

    // precondition: all values of u are smaller than all values of v
    static Node* join (Node* u, Node* v) {
        if (u == nullptr)
            return v;
        if (v == nullptr)
            return u;
        if (u->p > v->p) {
            u->right = join(u->right, v);
            return u;
        }
        v->left = join(u, v->left);
        return v;
    }

    static pair<Node*, Node*> split (Node* u, int k) {
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
        Node *curr = root;
        while (curr != nullptr) {
            if (curr->val < val)
                curr = curr->right;
            else if (curr->val > val)
                curr = curr->left;
            else
                return true;
        }
        return false;
    }

    void insert (int val) {
        if (contains(val))
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

int main () {
    Treap t;
    set<int> s;
    int N = 1000000;
    for (int i = 0; i < N; i++) {
        int val = rand();
        t.insert(val);
        s.insert(val);
    }

    for (auto i : s) {
        assert(t.contains(i));
        t.remove(i);
        assert(!t.contains(i));
    }
}
