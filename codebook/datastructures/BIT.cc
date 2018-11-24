/* Time: O(log N)
 * Memory: O(N)
 */

#include <bits/stdc++.h>

using namespace std;

struct BIT {
  int N;
  vector<int> val;
  BIT(int N) : N(N), val(N) {}

  void update(int idx, int v) {
    for (int x = idx; x < N; x += (x & -x))
      val[x] += v;
  }

  int query(int idx) {
    int ret = 0;
    for (int x = idx; x > 0; x -= (x & -x))
      ret += val[x];
    return ret;
  }
};
