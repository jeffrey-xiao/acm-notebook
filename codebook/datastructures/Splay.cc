/* Recently accessed elements are quick to access again.
 * Time: O(log N)
 * Memory: O(N)
 */

#include <bits/stdc++.h>

using namespace std;

struct Splay {
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

  Splay (): root(null) {}

  static void connect (Node* u, Node* v, int dir) {
    u->child[dir] = v;
    v->par = u;
  }

  // 0 = left, 1 = right;
  static Node* rotate (Node* u, int dir) {
    Node *c = u->child[dir ^ 1], *p = u->par, *pp = p->par;
    connect(p, c, dir);
    connect(u, p, dir ^ 1);
    connect(pp, u, getDir(p, pp));
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

  // closest node to val
  static Node* nodeAt (Node* u, int val) {
    if (u == null) return u;
    Node* ret = u;
    while (u != null) {
      ret = u;
      if (u->val < val) u = u->child[1];
      else if (u->val > val) u = u->child[0];
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
    if (v != null)
      v->par = u;
    return u;
  }

  static pair<Node*, Node*> split (Node* u, int val) {
    if (u == null) return {null, null};
    splay(u = nodeAt(u, val));

    if (u->val == val) {
      u->child[0]->par = u->child[1]->par = null;
      return {u->child[0], u->child[1]};
    } else if (u->val < val) {
      Node *ret = u->child[1];
      u->child[1] = (u->child[1]->par = null);
      return {u, ret};
    } else {
      Node *ret = u->child[0];
      u->child[0] = (u->child[0]->par = null);
      return {ret, u};
    }
  }

  bool contains (int val) {
    Node *curr = root;
    while (curr != null) {
      if (curr->val < val)
        curr = curr->child[1];
      else if (curr->val > val)
        curr = curr->child[0];
      else
        return true;
    }
    return false;
  }

  void insert (int val) {
    if (contains(val))
      return;
    auto res = split(root, val);
    root = new Node(val);
    root->par = null;
    root->child[0] = res.first, root->child[1] = res.second;
    if (root->child[0] != null)
      root->child[0]->par = root;
    if (root->child[1] != null)
      root->child[1]->par = root;
  }

  void remove (int val) {
    Node *curr = nodeAt(root, val);
    splay(curr);
    curr->child[0]->par = curr->child[1]->par = null;
    root = join(curr->child[0], curr->child[1]);
  }
};
