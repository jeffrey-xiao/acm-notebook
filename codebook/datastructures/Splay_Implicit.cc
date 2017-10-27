#include <bits/stdc++.h>
using namespace std;

int random () {
    return rand() * 65536 + rand();
}

struct Splay {
    struct Node {
        int val, sz;
        Node *child[2], *par;
        Node () {}
        Node (int val, int sz = 1): val(val), sz(sz) {
            child[0] = child[1] = par = this;
        }
    };

    Node *root;
    static Node *null;

    Splay () {
        null = new Node();
        null->child[0] = null->child[1] = null->par = null;
        null->sz = 0;
        root = null;
    }

    static void connect (Node* u, Node* v, int dir) {
        u->child[dir] = v;
        v->par = u;
    }

    static void update (Node* u) {
            if (u != null) u->sz = 1 + u->child[0]->sz + u->child[1]->sz;
    }

    // 0 = left, 1 = right;
    static Node* rotate (Node* u, int dir) {
        Node *c = u->child[dir ^ 1], *p = u->par, *pp = p->par;
        connect(p, c, dir);
        connect(u, p, dir ^ 1);
        connect(pp, u, getDir(p, pp));
        update(p);
        update(u);
        update(pp);
        return u;
    }

    static int getDir (Node* u, Node* p) {
        return p->child[0] == u ? 0 : 1;
    }

    static Node* splay (Node* u) {
        while (u->par != null) {
            Node *p = u->par, *pp = p->par;
            int dp = getDir(u, p), dpp = getDir(p, pp);
            if (pp == null) rotate(u, dp);
            else if (dp == dpp) rotate(p, dpp), rotate(u, dp);
            else rotate(u, dp), rotate(u, dpp);
        }
        return u;
    }

    static Node* nodeAt (Node* u, int index) {
        if (u == null) return u;
        Node* ret = u;
        while (u != null) {
            ret = u;
            if (u->child[0]->sz + 1 < index) index -= u->child[0]->sz + 1, u = u->child[1];
            else if (u->child[0]->sz + 1 > index) u = u->child[0];
            else return u;
        }
        return ret;
    }

    // precondition: all values of u are smaller than all values of v
    static Node* join (Node* u, Node* v) {
        if (u == null) return v;
        while (u->child[1] != null)
            u = u->child[1];
        splay(u);
        u->child[1] = v;
        update(u);
        if (v != null)
            v->par = u;
        return u;
    }

    static pair<Node*, Node*> split (Node* u, int index) {
        if (u == null) return {null, null};
        splay(u = nodeAt(u, index));

        if (u->child[0]->sz + 1 <= index) {
            Node *ret = u->child[1];
            u->child[1] = (u->child[1]->par = null);
            update(u);
            update(ret);
            return {u, ret};
        } else {
            Node *ret = u->child[0];
            u->child[0] = (u->child[0]->par = null);
            update(u);
            update(ret);
            return {ret, u};
        }
    }

    void modify (int index, int val) {
        Node *curr = root;
        while (curr != null) {
            if (curr->child[0]->sz + 1 < index)
                index -= curr->child[0]->sz + 1, curr = curr->child[1];
            else if (curr->child[0]->sz + 1 > index)
                curr = curr->child[0];
            else {
                curr->val = val;
                return;
            }
        }
    }

    void push_back (int val) {
        Node *u = new Node(val);
        u->child[0] = u->child[1] = u->par = null;
        root = join(root, u);
    }

    void insert (int index, int val) {
        auto res = split(root, index);
        root = new Node(val);
        root->par = null;
        root->child[0] = res.first, root->child[1] = res.second;
        update(root);
        if (root->child[0] != null)
            root->child[0]->par = root;
        if (root->child[1] != null)
            root->child[1]->par = root;
    }

    void remove (int index) {
        Node *curr = nodeAt(root, index);
        splay(curr);
        curr->child[0]->par = curr->child[1]->par = null;
        root = join(curr->child[0], curr->child[1]);
    }

    int get (int index) {
        return nodeAt(root, index)->val;
    }
};

Splay::Node* Splay::null = new Node(0, 0);

int main () {
    vector<int> l;
    Splay t;
    for (int i = 0; i < 100000; i++) {
        int rnd = abs(random()) % (i + 1);
        int val = random();
        l.insert(l.begin() + rnd, val);
        t.insert(rnd, val);
    }

    for (int i = 0; i < 100000; i++) {
        fflush(stdin);
        assert(l[i] == t.get(i + 1));
    }

    t.root = t.null;
    for (int i = 0; i < 1000000; i++) {
        int rnd = abs(random()) % (i + 1);
        int val = random();

        t.insert(rnd, val);
    }


    for (int i = 0; i < 1000000; i++) {
        int rnd = abs(random()) % (1000000);
        int val = random();

        t.modify(rnd, val);
        assert(t.get(rnd) == val);
    }

    for (int i = 999999; i >= 0; i--) {
        int rnd = abs(random()) % (i + 1) + 1;
        int prev = t.get(rnd);
        t.remove(rnd);
        if (rnd < t.root->sz)
            assert(prev != t.get(rnd));
    }

    return 0;
}
