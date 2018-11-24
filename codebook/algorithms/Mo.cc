/* Determining the number of distinct numbers in a subsequence
 * Time: O(M sqrt(N))
 * Memory: O(M + N + MAX_VALUE)
 */

#include <bits/stdc++.h>

#define SIZE 30010
#define MAX_VALUE 1000010
#define QUERIES 200010

using namespace std;

int N, M, sz, res, cnt[MAX_VALUE], a[SIZE], ans[QUERIES];

struct Query {
  int l, r, index;
  Query() {}
  Query(int l, int r, int index) : l(l), r(r), index(index) {}
  bool operator<(const Query &q) const {
    if ((l - 1) / sz != (q.l - 1) / sz)
      return (l - 1) / sz > (q.l - 1) / sz;
    return r < q.r;
  }
} q[QUERIES];

void update(int i) {
  if (!cnt[i]++)
    res++;
}

void remove(int i) {
  if (!--cnt[i])
    res--;
}

int main() {
  scanf("%d", &N);
  sz = (int)sqrt(N);

  for (int i = 1; i <= N; i++)
    scanf("%d", &a[i]);

  scanf("%d", &M);
  for (int i = 0; i < M; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    q[i] = Query(l, r, i);
  }

  sort(q, q + M);
  int l = 1, r = 0;
  for (int i = 0; i < M; i++) {
    while (r > q[i].r)
      remove(a[r--]);
    while (r < q[i].r)
      update(a[++r]);
    while (l < q[i].l)
      remove(a[l++]);
    while (l > q[i].l)
      update(a[--l]);
    ans[q[i].index] = res;
  }

  for (int i = 0; i < M; i++)
    printf("%d\n", ans[i]);
  return 0;
}
