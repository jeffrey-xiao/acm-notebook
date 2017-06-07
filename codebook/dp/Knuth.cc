/* Requirements:
 *  - dp[i][j] = min(dp[i][k] + dp[k][j] + C[i][j]) where i < k < j
 *  - min[i][j - 1] <= min[i][j] <= min[i + 1][j],
 *    min[i][j] = smallest k for optimal answer
 *
 * A certain string-processing language allows the programmer to
 * break a string into two pieces. Since this involves copying the
 * old string, it cost N units of time to break a string of N
 * characters into two pieces. Suppose you want to break a string into
 * many pieces. The order in which the breaks are made can affect the
 * total amount of time.
 *
 * Given the length of the string N, and M places to break the string at,
 * what is the minimum amount of time to break the string?
 */


#include <bits/stdc++.h>
#define SIZE 1005

typedef long long ll;

ll dp[SIZE][SIZE];
int mid[SIZE][SIZE];
int pos[SIZE];
int N, M;

int main () {
    while (scanf("%d%d", &N, &M) != EOF) {
        for (int i = 1; i <= M; i++)
            scanf("%d", &pos[i]);
        pos[0] = 0;
        pos[M + 1] = N;

        for (int i = 0; i <= M + 1; i++) {
            for (int j = 0; j + i <= M + 1; j++) {
                if (i < 2) {
                    dp[j][j + i] = 0LL;
                    mid[j][j + i] = j;
                    continue;
                }
                dp[j][j + i] = 1LL << 60;
                for (int k = mid[j][i + j - 1]; k <= mid[j + 1][i + j]; k++) {
                    ll next = dp[j][k] + dp[k][j + i] + pos[j + i] - pos[j];
                    if (next < dp[j][j + i]) {
                        dp[j][j + i] = next;
                        mid[j][j + i] = k;
                    }
                }
            }
        }

        printf("%lld\n", dp[0][M + 1]);
    }
    return 0;
}
