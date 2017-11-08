#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> getPrimesEratosthenes (int N) {
  vector<bool> prime (N + 1);
  vector<int> ret;

  fill(prime.begin(), prime.end(), true);

  for (int i = 2; i * i <= N; i++)
    if (prime[i])
      for (int j = i * i; j <= N; j += i)
        prime[j] = false;

  for (int i = 2; i <= N; i++)
    if (prime[i])
      ret.push_back(i);

  return ret;
}

vector<int> eulerTotient (int N) {
  vector<int> ret (N + 1);
  for (int i = 1; i <= N; i++)
    ret[i] = i;
  for (int i = 2; i <= N; i++)
    if (ret[i] == i)
      for (int j = i; j <= N; j += i)
        ret[j] -= ret[j] / i;
  return ret;
}

ll gcd (ll a, ll b) {
  return b == 0 ? a : gcd(b, a % b);
}

ll multmod (ll a, ll b, ll m) {
  ll x = 0, y = a % m;
  for (; b > 0; b >>= 1) {
    if ((b & 1) == 1)
      x = (x + y) % m;
    y = (y << 1) % m;
  }
  return x % m;
}

ll randLong () {
  return ((rand() * 1LL) << 47) | ((rand() * 1LL) << 32) | ((rand() * 1LL) << 16) | rand();
}

ll brent (ll n) {
  if (n % 2 == 0)
    return 2;
  ll y = randLong() % (n - 1) + 1;
  ll c = randLong() % (n - 1) + 1;
  ll m = randLong() % (n - 1) + 1;
  ll g = 1, r = 1, q = 1, ys = 0, hi = 0, x = 0;
  while (g == 1) {
    x = y;

    for (int i = 0; i < r; i++)
      y = (multmod(y, y, n) + c) % n;

    for (ll k = 0; k < r && g == 1; k += m) {
      ys = y;
      hi = min(m, r - k);
      for (int j = 0; j < hi; j++) {
        y = (multmod(y, y, n) + c) % n;
        q = multmod(q, x > y ? x - y : y - x, n);
      }
      g = gcd(q, n);
    }

    r *= 2;
  }

  if (g == n)
    do {
      ys = (multmod(ys, ys, n) + c) % n;
      g = gcd(x > ys ? x - ys : ys - x, n);
    } while (g <= 1);

  return g;
}
