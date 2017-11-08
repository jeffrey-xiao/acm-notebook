/* Time: O(N)
 * Memory: O(N)
 */

#include <bits/stdc++.h>

using namespace std;

string getLongestPalindrome (string s) {
  int len = (int)s.size() * 2 + 1;
  char text[len];
  for (int i = 0; i < len; i++)
    text[i] = '#';
  for (int i = 1; i < len; i += 2)
    text[i] = s[i / 2];
  int maxLen[len];
  memset(maxLen, 0, sizeof maxLen);

  int c = 0, r = 0;
  for (int i = 1; i < len; i++) {
    int j = (c - (i - c));
    maxLen[i] = r > i ? min(r - i, maxLen[j]) : 0;
    while (i + 1 + maxLen[i] < len && i - 1 - maxLen[i] >= 0 && text[i + 1 + maxLen[i]] == text[i - 1 - maxLen[i]])
      maxLen[i]++;

    if (i + maxLen[i] > r) {
      r = i + maxLen[i];
      c = i;
    }
  }

  int maxLength = 0;
  int index = 0;
  for (int i = 1; i < len - 1; i++) {
    int currLen = maxLen[i];
    if (currLen > maxLength) {
      maxLength = currLen;
      index = i;
    }
  }
  maxLength = maxLength + (index - maxLength) % 2;
  return s.substr((index - maxLength + 1) / 2, maxLength);
}
