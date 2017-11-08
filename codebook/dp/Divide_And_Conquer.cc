/* Requirements:
 *  - dp[i][j] = min(dp[i - 1][k] + C[k][j]) where k < j
 *  - min[i][j] <= min[i][j + 1], min[i][j] = smallest k for optimal ans
 *
 * There are N people at an amusement park who are in a queue for a ride.
 * Each pair of people has a measured level of unfamiliarity. The people
 * will be divided into K non-empty contiguous groups. Each division has
 * a total unfamiliarity value which is the sum of the levels of
 * unfamiliarty between any pair of people for each group
 *
 * Time Improvement: O(KN^2) -> O(KN log N)
 * Memory: O(KN)
 */

#include <bits/stdc++.h>

#define MAX_N 4001
#define MAX_K 801
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
using namespace std;

int N, K;
int A[MAX_N][MAX_N];
int dp[MAX_K][MAX_N];

void compute (int g, int i, int j, int l, int r) {
  if (i > j)
    return;
  int mid = (i + j) >> 1;
  int bestIndex = l;
  for (int k = l; k <= min(mid, r); k++) {
    int val = dp[g - 1][k - 1] + (A[mid][mid] - A[mid][k - 1] - A[k - 1][mid] + A[k - 1][k - 1]);
    if (val < dp[g][mid]) {
      dp[g][mid] = val;
      bestIndex = k;
    }
  }
  compute(g, i, mid - 1, l, bestIndex);
  compute(g, mid + 1, j, bestIndex, r);
}

int main () {
  scan(N);
  scan(K);

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      scan(A[i][j]);
      A[i][j] += A[i - 1][j] + A[i][j - 1] - A[i - 1][j - 1];
    }
  }

  for (int i = 0; i <= K; i++)
    for (int j = 0; j <= N; j++)
      dp[i][j] = 1 << 30;
  dp[0][0] = 0;

  for (int i = 1; i <= K; i++)
    compute(i, 1, N, 1, N);

  printf("%d\n", dp[K][N] / 2);
  return 0;
}
