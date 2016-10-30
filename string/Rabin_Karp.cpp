#include <bits/stdc++.h>
#define MOD 1000000007L
#define R 256L
using namespace std;
typedef long long ll;
struct RabinKarp {
    ll pow, patternHash;
    string pattern;
    RabinKarp (string pattern): pattern(pattern) {
        initialize();
    }

    ll getHash (string s, int len) {
        ll ret = 0;
        for (int i = 0; i < len; i++)
            ret = (R * ret + s[i]) % MOD;
        return ret;
    }

    void initialize () {
        patternHash = getHash(pattern, pattern.size());
        pow = 1;
        for (int i = 0; i < (int)pattern.size() - 1; i++)
            pow = (pow * R) % MOD;
    }

    int search (string text) {
        if (pattern.size() > text.size())
            return -1;
        ll currHash = getHash(text, pattern.size());
        if (currHash == patternHash)
            return 0;
        for (int i = (int)pattern.size(); i < (int)text.size(); i++) {
            currHash = ((currHash - pow * text[i - (int)pattern.size()]) % MOD + MOD) % MOD;
            currHash = (currHash * R + text[i]) % MOD;
            if (currHash == patternHash)
                return i - (int)pattern.size() + 1;
        }
        return -1;
    }
};
