/*
 * Produces an array Z where Z[i] is the length of the longest substring
 * starting from S[i] which is also a prefix of S.
 */
#include <bits/stdc++.h>
using namespace std;

vector<int> compute (string s) {
    vector<int> z(s.size());
    int l = 0, r = 0;
    for (int i = 1; i < (int)s.size(); i++) {
        if (i > r) {
            l = r = i;
            while (r < (int)s.size() && s[r] == s[r - l])
                r++;
            r--;
            z[i] = r - l + 1;
        } else {
            int j = i - l;
            if (z[j] < r - i + 1)
                z[i] = z[j];
            else {
                l = i;
                while (r < (int)s.size() && s[r] == s[r - l])
                    r++;
                r--;
                z[i] = r - l + 1;
            }
        }
    }
    return z;
}
