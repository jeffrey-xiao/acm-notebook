#include <bits/stdc++.h>
typedef long long ll;

ll modpow (ll base, ll pow, ll mod) {
    if (pow == 0)
        return 1L;
    if (pow == 1)
        return base;
    if (pow % 2)
        return base * modpow(base * base % mod, pow / 2, mod) % mod;
    return modpow(base * base % mod, pow / 2, mod);
}

ll factorial (ll n, ll m) {
    ll ret = 1;
    for (int i = 2; i <= n; i++)
        ret = (ret * i) % m;
    return ret;
}

// precondition: p is prime
ll divMod (ll i, ll j, ll p) {
    return i * modpow(j, p - 2, p) % p;
}

// precondition: p is prime; O(log P) if you precompute factorials
ll fastChoose (ll n, ll k, ll p) {
    return divMod(divMod(factorial(n, p), factorial(k, p), p), factorial(n - k, p), p);
}

// number of partitions of n
ll partitions (ll n, ll m) {
    ll dp[n + 1];
    memset(dp, 0, sizeof dp);
    dp[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            dp[j] = (dp[j] + dp[j - 1]) % m;
    return dp[n] % m;
}

ll stirling1 (int n, int k, long m) {
    ll dp[n + 1][k + 1];
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k; j++) {
            dp[i][j] = ((i - 1) * dp[i - 1][j]) % m;
            dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % m;
        }
    return dp[n][k];
}

ll stirling2 (int n, int k, ll m) {
    ll dp[n + 1][k + 1];
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k; j++) {
            dp[i][j] = (j * dp[i - 1][j]) % m;
            dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % m;
        }
    return dp[n][k];
}

ll eulerian1 (int n, int k, ll m) {
    if (k > n - 1 - k)
        k = n - 1 - k;
    ll dp[n + 1][k + 1];
    memset(dp, 0, sizeof dp);
    for (int j = 1; j <= k; j++)
        dp[0][j] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k; j++) {
            dp[i][j] = ((i - j) * dp[i - 1][j - 1]) % m;
            dp[i][j] = (dp[i][j] + ((j + 1) * dp[i - 1][j]) % m) % m;
        }
    return dp[n][k] % m;
}

ll eulerian2 (int n, int k, ll m) {
    ll dp[n + 1][k + 1];
    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k; j++) {
            if (i == j) {
                dp[i][j] = 0;
            } else {
                dp[i][j] = ((j + 1) % dp[i - 1][j]) % m;
                dp[i][j] = (((2 * i - 1 - j) * dp[i - 1][j - 1]) % m + dp[i][j]) % m;
            }
        }
    return dp[n][k] % m;
}

// precondition: p is prime
ll catalan (int n, ll p) {
    return fastChoose(2 * n, n, p) * modpow(n + 1, p - 2, p) % p;
}
