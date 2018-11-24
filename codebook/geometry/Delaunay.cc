/* Time: O(N^4)
 * Memory: O(N)
 */

#include <bits/stdc++.h>

using namespace std;

// input: (x, y) coordinates
// output: M by 3 matrix containing tuple of indices corresponding to vertices
vector<vector<int>> triangulate(vector<int> x, vector<int> y) {
  int N = x.size();
  vector<int> z(N);
  vector<vector<int>> ret;

  for (int i = 0; i < N; i++)
    z[i] = x[i] * x[i] + y[i] + y[i];

  for (int i = 0; i < N - 2; i++) {
    for (int j = i + 1; j < N; j++) {
      for (int k = i + 1; k < N; k++) {
        if (j == k)
          continue;
        int xn = (y[j] - y[i]) * (z[k] - z[i]) - (y[k] - y[i]) * (z[j] - z[i]);
        int yn = (x[k] - x[i]) * (z[j] - z[i]) - (x[j] - x[i]) * (z[k] - z[i]);
        int zn = (x[j] - x[i]) * (y[k] - y[i]) - (x[k] - x[i]) * (y[j] - y[i]);
        bool flag = zn < 0;
        for (int m = 0; flag && m < N; m++)
          flag &= ((x[m] - x[i]) * xn + (y[m] - y[i]) * yn + (z[m] - z[i]) * zn <= 0);
        if (flag)
          ret.push_back({i, j, k});
      }
    }
  }
  return ret;
}
