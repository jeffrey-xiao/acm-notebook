/* Time: O(N) query; O(N) construction
 * Memory: O(N)
 */

#include <bits/stdc++.h>

using namespace std;

struct KMP {
  string pattern;
  vector<int> lcp;
  KMP (string pattern): pattern(pattern), lcp(pattern.size()) {
    buildLcp();
  }

  void buildLcp () {
    for (int i = 1; i < (int)pattern.size(); i++) {
      int j = lcp[i - 1];
      while (j > 0 && pattern[j] != pattern[i])
        j = lcp[j - 1];
      if (pattern[j] == pattern[i])
        j++;
      lcp[i] = j;
    }
    for (int i = 0; i < (int)pattern.size(); i++)
      printf("%d\n", lcp[i]);
  }

  int search (string text) {
    int j = 0;
    for (int i = 0; i < (int)text.size(); i++) {
      while (j > 0 && text[i] != pattern[j])
        j = lcp[j - 1];
      if (text[i] == pattern[j])
        j++;
      if (j == (int)pattern.size())
        return i - j + 1;
    }
    return -1;
  }
};
