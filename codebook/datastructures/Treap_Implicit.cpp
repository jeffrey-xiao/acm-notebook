#include <bits/stdc++.h>
using namespace std;
int randomPriority () {
    return rand() * 65536 + rand();
}
struct Node {
    int val, p, sz;
    Node *left, *right;
    Node (int val): val(val), p(randomPriority()), sz(1), left(nullptr), right(nullptr) {}
};

int getSize (Node* u) {
    return u == nullptr ? 0 : u->sz;
}

void update (Node* u) {
    if (u) u->sz = 1 + getSize(u->left) + getSize(u->right);
}

struct Treap {
    Node* root;

    Treap (): root(nullptr) {}

    // precondition: all values of u are smaller than all values of v
    Node* join (Node* u, Node* v) {
        if (u == nullptr)
            return v;
        if (v == nullptr)
            return u;
        if (u->p > v->p) {
            u->right = join(u->right, v);
            update(u);
            return u;
        }
        v->left = join(u, v->left);
        update(v);
        return v;
    }

    pair<Node*, Node*> split (Node* u, int k) {
        if (u == nullptr)
            return make_pair(nullptr, nullptr);
        if (getSize(u->left) + 1 > k) {
            auto res = split(u->left, k);
            u->left = res.second;
            res.second = u;
            update(res.first);
            update(res.second);
            return res;
        } else {
            auto res = split(u->right, k - getSize(u->left) - 1);
            u->right = res.first;
            res.first = u;
            update(res.first);
            update(res.second);
            return res;
        }
    }

    void modify (int index, int val) {
        Node *curr = root;
        while (curr != nullptr) {
            if (getSize(curr->left) + 1 < index)
                index -= getSize(curr->left) + 1, curr = curr->right;
            else if (getSize(curr->left) + 1 > index)
                curr = curr->left;
            else {
                curr->val = val;
                return;
            }
        }
    }

    int get (int index) {
        Node *curr = root;
        while (curr != nullptr) {
            if (getSize(curr->left) + 1 < index)
                index -= getSize(curr->left) + 1, curr = curr->right;
            else if (getSize(curr->left) + 1 > index)
                curr = curr->left;
            else
                return curr->val;
        }
        return -1;
    }

    void push_back (int val) {
        root = join(root, new Node(val));
    }

    void insert (int index, int val) {
        auto res = split(root, index);
        root = join(res.first, join(new Node(val), res.second));
    }

    void remove (int index) {
        auto nodes = split(root, index);
        root = join(nodes.first->left, join(nodes.first->right, nodes.second));
    }
};

int main () {
    vector<int> l;
    Treap t;
    for (int i = 0; i < 100000; i++) {
        int rnd = abs(randomPriority()) % (i + 1);
        int val = randomPriority();
        l.insert(l.begin() + rnd, val);
        t.insert(rnd, val);
    }

    for (int i = 0; i < 100000; i++) {
        assert(l[i] == t.get(i + 1));
    }

    t.root = nullptr;
    for (int i = 0; i < 1000000; i++) {
        int rnd = abs(randomPriority()) % (i + 1);
        int val = randomPriority();

        t.insert(rnd, val);
    }


    for (int i = 0; i < 1000000; i++) {
        int rnd = abs(randomPriority()) % (1000000);
        int val = randomPriority();

        t.modify(rnd, val);
        assert(t.get(rnd) == val);
    }

    for (int i = 999999; i >= 0; i--) {
        int rnd = abs(randomPriority()) % (i + 1) + 1;
        int prev = t.get(rnd);
        t.remove(rnd);
        if (rnd < getSize(t.root))
            assert(prev != t.get(rnd));
    }
    return 0;
}
