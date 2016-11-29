// What would be the k-th number in (A[i], A[i + 1], ..., A[j]) if this segment was sorted?
#include <bits/stdc++.h>
#define SIZE 100001
using namespace std;
struct Node {
    int cnt;
    Node *left, *right;
    Node (int cnt): cnt(cnt) {}
    Node (int cnt, Node *left, Node *right): cnt(cnt), left(left), right(right) {}
};

struct Tree {
    int N;
    vector<Node*> val;
    Tree () {}
    Tree (int N): N(N), val(N + 1) {
        val[0] = new Node(0);
        val[0]->left = val[0]->right = val[0];
    }

    Node* update (Node* prev, int l, int r, int val) {
        if (l <= val && val <= r) {
            if (l == r)
                return new Node(prev->cnt + 1);
            int mid = (l + r) >> 1;
            return new Node(prev->cnt + 1, update(prev->left, l, mid, val), update(prev->right, mid + 1, r, val));
        }
        return prev;
    }

    int query (Node* lo, Node* hi, int l, int r, int val) {
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        int cnt = hi->left->cnt - lo->left->cnt;
        if (val <= cnt)
            return query(lo->left, hi->left, l, mid, val);
        else
            return query(lo->right, hi->right, mid + 1, r, val - cnt);
    }
};

int N, Q;
set<int> ts;
int toVal[SIZE], a[SIZE];
unordered_map<int, int> toIndex;
Tree t(SIZE);

int main () {
    scanf("%d%d", &N, &Q);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &a[i]);
        ts.insert(a[i]);
    }
    int cnt = 0;
    for (int val : ts) {
        toIndex[val] = ++cnt;
        toVal[cnt] = val;
    }

    for (int i = 1; i <= N; i++)
        t.val[i] = t.update(t.val[i - 1], 1, cnt, toIndex[a[i]]);

    for (int i = 0; i < Q; i++) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", toVal[t.query(t.val[l - 1], t.val[r], 1, cnt, k)]);
    }
}

