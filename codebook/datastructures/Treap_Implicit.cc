/* The key of each element is the array index of the element.
 * Time: O(log N)
 * Memory: O(N)
 */

#include <bits/stdc++.h>

using namespace std;

struct Treap {
  struct Node {
    int val, p, sz;
    Node *left, *right;
    Node (int val): val(val), p(randomPriority()), sz(1), left(nullptr), right(nullptr) {}
  };

  static int randomPriority () {
    return rand() * 65536 + rand();
  }

  static int getSize (Node* u) {
    return u == nullptr ? 0 : u->sz;
  }

  static void update (Node* u) {
    if (u) u->sz = 1 + getSize(u->left) + getSize(u->right);
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
      update(u);
      return u;
    }
    v->left = join(u, v->left);
    update(v);
    return v;
  }

  static pair<Node*, Node*> split (Node* u, int k) {
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
