/* Time: O(N) for any interlaced sequence of addLine and getMax calls
 * Time: O(N)
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

struct ConvexHullTrick {
  vector<LL> M, B;
  int ptr = 0;

  void addLine(LL m, LL b) {
    int len = M.size();
    while (len > 1 && (B[len - 2] - B[len - 1]) * (m - M[len - 1]) >=
                          (B[len - 1] - b) * (M[len - 1] - M[len - 2]))
      len--;
    M.resize(len);
    B.resize(len);
    M.push_back(m);
    B.push_back(b);
  }

  LL getMax(LL x) {
    if (ptr >= (int)M.size())
      ptr = (int)M.size() - 1;
    while (ptr < (int)M.size() - 1 && M[ptr + 1] * x + B[ptr + 1] >= M[ptr] * x + B[ptr])
      ptr++;
    return M[ptr] * x + B[ptr];
  }
};
