#include <bits/stdc++.h>
using namespace std;

struct Suffix {
    int index;
    pair<int, int> rank;
    Suffix () {}
    Suffix (int index, int rank1, int rank2): index(index), rank{rank1, rank2} {}
    bool operator < (const Suffix& s) const {
        return rank < s.rank;
    }
    bool operator == (const Suffix& s) const {
        return rank == s.rank;
    }
};

vector<int> buildSuffixArray (string s) {
    int N = (int)s.size();
    vector<Suffix> suff(N);
    vector<int> ind(N), ret(N);

    for (int i = 0; i < N; i++)
        suff[i] = Suffix(i, s[i], i + 1 < N ? s[i + 1] : -1);

    for (int i = 2;; i <<= 1) {
        sort(suff.begin(), suff.end());
        ind[suff[0].index] = 0;
        for (int j = 1; j < N; j++)
            ind[suff[j].index] = (suff[j] == suff[j - 1] ? 0 : 1) + ind[suff[j - 1].index];
        for (int j = 0; j < N; j++) {
            suff[j].rank.second = suff[j].index + i < N ? ind[suff[j].index + i] : -1;
            suff[j].rank.first = ind[suff[j].index];
        }
        if ((*--suff.end()).rank.first == N - 1)
            break;
    }
    for (int i = 0; i < N; i++)
        ret[ind[i]] = i;
    return ret;
}
