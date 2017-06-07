#include <bits/stdc++.h>

using namespace std;

struct LinkCut {
    struct Node {
        int index, sz;
        Node *child[2], *par, *pathPar;
        Node (int index, int sz): index(index), sz(sz) {
            child[0] = this;
            child[1] = this;
            par = this;
            pathPar = this;
        }
    };

    static Node *null;
    vector<Node*> nodes;

    LinkCut (int N): nodes(N) {
        for (int i = 0; i < N; i++) {
            nodes[i] = new Node(i, 1);
            nodes[i]->child[0] = nodes[i]->child[1] = nodes[i]->par = nodes[i]->pathPar = null;
        }
    }

    static void update (Node *u) {
        if (u == null)
            return;
        u->sz = 1 + u->child[0]->sz + u->child[1]->sz;
    }

    static int getDir (Node *u, Node *p) {
        return p->child[0] == u ? 0 : 1;
    }

    static void connect (Node* u, Node* v, int dir) {
        u->child[dir] = v;
        v->par = u;
    }

    static Node* rotate (Node* u, int dir) {
        Node *c = u->child[dir ^ 1], *p = u->par, *pp = p->par;
        connect(p, c, dir);
        connect(u, p, dir ^ 1);
        connect(pp, u, getDir(p, pp));

        u->pathPar = p->pathPar;
        p->pathPar = null;
        update(p);
        update(u);
        update(pp);
        return u;
    }

    static void splay (Node *u) {
        while (u->par != null) {
            Node *p = u->par, *pp = p->par;
            int dp = getDir(u, p), dpp = getDir(p, pp);
            if (pp == null) rotate(u, dp);
            else if (dp == dpp) rotate(p, dpp), rotate(u, dp);
            else rotate(u, dp), rotate(u, dpp);
        }
    }

    static Node* access (Node* u) {
        Node *prev = null;
        for (Node *v = u; v != null; v = v->pathPar) {
            splay(v);
            if (v->child[1] != null) {
                v->child[1]->pathPar = v;
                v->child[1]->par = null;
                v->child[1] = null;
            }
            v->child[1] = prev;
            update(v);
            if (prev != null) {
                prev->par = v;
                prev->pathPar = null;
            }
            prev = v;
        }
        splay(u);
        return prev;
    }

    // precondition: n must be a root node, and n and m must be in different trees
    static void link (Node *n, Node *m) {
        access(n);
        access(m);
        n->child[0] = m;
        m->par = n;
        update(n);
    }

    // precondition: n must not be a root node
    static void cut (Node *n) {
        access(n);
        if (n->child[0] != null) {
            n->child[0]->par = null;
            n->child[0] = null;
        }
        update(n);
    }

    static Node* getRoot (Node *n) {
        access(n);
        while (n->child[0] != null)
            n = n->child[0];
        access(n);
        return n;
    }

    static int getHeight (Node *n) {
        access(n);
        return n->child[0]->sz + 1;
    }

    static int lca (Node *u, Node *v) {
        access(u);
        return access(v)->index;
    }
};

LinkCut::Node* LinkCut::null = new Node(-1, 0);
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
int main () {
    int N, M;
    scan(N);
    scan(M);

    LinkCut t(N);

    for (int i = 0; i < M; i++) {
        char in[5] ;
        int j = 0, ch;
        while( ( ( ch = getchar() ) != '\n' ) && ( ch != ' ' ) && ( j < ( 5 - 1 ) ) )
           in[j++]=ch;
        in[j]='\0';
        int u, v;
        scan(u);
        scan(v);
        u--, v--;
        if (in[0] == 'a') {
            t.link(t.getRoot(t.nodes[u]), t.nodes[v]);
        }
        else if (in[0] == 'r') {
            if (t.nodes[v]->par == t.nodes[u] || t.nodes[v]->pathPar == t.nodes[u])
                t.cut(t.nodes[v]);
            else
                t.cut(t.nodes[u]);
        } else {
            if (t.getRoot(t.nodes[u]) == t.getRoot(t.nodes[v]))
                puts("YES");
            else
                puts("NO");
        }
    }
    return 0;
}
