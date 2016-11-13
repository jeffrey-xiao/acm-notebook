#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

struct Line {
    ll m, b, val;
    ld xVal;
    bool isQuery;

    Line (ll m, ll b, ll val, bool isQuery): m(m), b(b), val(val), xVal(-numeric_limits<double>::max()), isQuery(isQuery) {}

    bool isParallel (const Line& l) const {
        return m == l.m;
    }

    ld intersect (const Line& l) const {
        if (isParallel(l))
            return numeric_limits<double>::max();
        return (ld)(l.b - b) / (m - l.m);
    }

    bool operator < (const Line& l) const {
        if (l.isQuery)
            return l.val < xVal;
        return m < l.m;
    }
};

typedef set<Line>::iterator iter;

struct ConvexHullTrick {
    set<Line> hull;

    bool hasPrev (iter it) {
        return it != hull.begin();
    }

    bool hasNext (iter it) {
        return (it != hull.end()) && (++it != hull.end());
    }

    bool isIrrelevant (iter it) {
        if (!hasPrev(it) || !hasNext(it))
            return false;
        iter prev = it, next = it;
        prev--, next++;
        return next->intersect(*prev) <= next->intersect(*it);
    }

    iter updateIntersections (iter it) {
        if (!hasNext(it))
            return it;
        iter it2 = it;
        double val = it->intersect(*++it2);
        Line l(*it);
        l.xVal = val;
        hull.erase(it++);
        return hull.insert(++it, l);
    }

    void addLine (ll m, ll b) {
        Line l(m, b, 0, false);
        iter it = hull.lower_bound(l);

        if (it != hull.end() && it->isParallel(l)) {
            if (b < it->b)
                hull.erase(it);
            else
                return;
        }

        it = hull.insert(it, l);
        if (isIrrelevant(it)) {
            hull.erase(it);
            return;
        }

        while (hasPrev(it) && isIrrelevant(--it))
            hull.erase(it++);
        while (hasNext(it) && isIrrelevant(++it))
            hull.erase(it--);

        it = updateIntersections(it);
        if (hasPrev(it))
            updateIntersections(--it);
        if (hasNext(++it))
            updateIntersections(++it);
    }

    ll getBest (ll x) const {
        Line q(0, 0, x, true);
        iter it = hull.lower_bound(q);
        return it->m * x + it->b;
    }
};
