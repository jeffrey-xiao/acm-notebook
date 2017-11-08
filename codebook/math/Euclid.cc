#include <bits/stdc++.h>

using namespace std;

int mod (int a, int b) {
  return ((a % b) + b) % b;
}

int gcd (int a, int b) {
  return b == 0 ? a : (gcd(b, a % b));
}

int lcm (int a, int b) {
  return a / gcd(a, b) * b;
}

// returns (d, x, y) such that d = gcd(a, b) and d = ax * by
vector<int> euclid (int a, int b) {
  int x = 1, y = 0, x1 = 0, y1 = 1, t;
  while (b != 0) {
    int q = a / b;
    t = x;
    x = x1;
    x1 = t - q * x1;
    t = y;
    y = y1;
    y1 = t - q * y1;
    t = b;
    b = a - q * b;
    a = t;
  }
  vector<int> ret = {a, x, y};
  if (a <= 0) ret = {-a, -x, -y};
  return ret;
}

// finds all solutions to ax = b mod n
vector<int> linearEquationSolver (int a, int b, int n) {
  vector<int> ret;
  vector<int> res = euclid(a, b);
  int d = res[0], x = res[1];

  if (b % d == 0) {
    x = mod(x * (b / d), n);
    for (int i = 0; i < d; i++)
      ret.push_back(mod(x + i * (n / d), n));
  }

  return ret;
}

// computes x and y such that ax + by = c; on failure, x = y = -1 << 30
void linearDiophantine (int a, int b, int c, int &x, int &y) {
  int d = gcd(a, b);

  if (c % d != 0) {
    x = y = -(1 << 30);
  } else {
    a /= d;
    b /= d;
    c /= d;
    vector<int> ret = euclid(a, b);
    x = ret[1] * c;
    y = ret[2] * c;
  }
}

// precondition: m > 0 && gcd(a, m) = 1
int modInverse (int a, int m) {
  a = mod(a, m);
  return a == 0 ? 0 : mod((1 - modInverse(m % a, a) * m) / a, m);
}

// precondition: p is prime
vector<int> generateInverse (int p) {
  vector<int> res(p);
  res[1] = 1;
  for (int i = 2; i < p; ++i)
    res[i] = (p - (p / i) * res[p % i] % p) % p;
  return res;
}

// solve x = a[i] (mod p[i]), where gcd(p[i], p[j]) == 1
int simpleRestore (vector<int> a, vector<int> p) {
  int res = a[0];
  int m = 1;
  for (int i = 1; i < (int)a.size(); i++) {
    m *= p[i - 1];
    while (res % p[i] != a[i])
      res += m;
  }
  return res;
}

int garnerRestore (vector<int> a, vector<int> p) {
  vector<int> x(a.size());
  for (int i = 0; i < (int)x.size(); ++i) {
    x[i] = a[i];
    for (int j = 0; j < i; ++j) {
      x[i] = (int) modInverse(p[j], p[i]) * (x[i] - x[j]);
      x[i] = (x[i] % p[i] + p[i]) % p[i];
    }
  }
  int res = x[0];
  int m = 1;
  for (int i = 1; i < (int)a.size(); i++) {
    m *= p[i - 1];
    res += x[i] * m;
  }
  return res;
}
