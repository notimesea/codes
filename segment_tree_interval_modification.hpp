#include <bits/stdc++.h>
using namespace std;

struct segmentTree {

    inline int modifyOperation(int x, int y) {
        return x + y;
    }

    // query (or combine) operation
    inline int queryOperation(int leftValue, int rightValue) {
        return max(leftValue, rightValue);
    }

    inline int deltaEffectOnSegment(int delta, int segmentLength) {
        // Here you must write a fast equivalent of following slow code:
        // int result = delta;
        // for (int i = 1; i < segmentLength; i++) result = queryOperation(result, delta);
        // return result;
        return delta;
    }

    inline int getNeutralDelta() {
        return 0;
    }

    inline int getInitValue() {
        return 0;
    }

    // generic code
    int n;
    vector<int> value;
    vector<int> keys;
    vector<int> delta; // delta[i] affects value[i], delta[2*i+1] and delta[2*i+2]
    vector<int> len;

    int joinValueWithDelta(int value, int delta) {
        if (delta == getNeutralDelta()) return value;
        return modifyOperation(value, delta);
    }

    int joinDeltas(int delta1, int delta2) {
        if (delta1 == getNeutralDelta()) return delta2;
        if (delta2 == getNeutralDelta()) return delta1;
        return modifyOperation(delta1, delta2);
    }

    void pushDelta(int i) {
        int d = 0;
        for (; (i >> d) > 0; d++) {
        }
        for (d -= 2; d >= 0; d--) {
            int x = i >> d;
            value[x >> 1] = joinValueWithDelta(x >> 1);
            delta[x] = joinDeltas(delta[x], delta[x >> 1]);
            delta[x ^ 1] = joinDeltas(delta[x ^ 1], delta[x >> 1]);
            delta[x >> 1] = getNeutralDelta();
        }
    }

    void init() {
        n = keys.size();
        value.resize(n + n);
        for (int i = 0; i < n; i++) {
            value[i + n] = getInitValue();
        }
        for (int i = 2 * n - 1; i > 1; i -= 2) {
            value[i >> 1] = queryOperation(value[i], value[i ^ 1]);
        }
        delta.assign(n + n, getNeutralDelta());
        len.resize(n + n);
        for (int i = 0; i < n; ++i) {
            len[i + n] = 1;
        }
        for (int i = 2 * n - 1; i > 1; i -= 2) {
            len[i >> 1] = len[i] + len[i ^ 1];
        }
    }

    int joinValueWithDelta(int i) {
        return joinValueWithDelta(value[i], deltaEffectOnSegment(delta[i], len[i]));
    }

    int query(int from, int to) {
        from = lower_bound(all(keys), from) - keys.begin();
        to = upper_bound(all(keys), to) - keys.begin() - 1;
        from += n;
        to += n;
        pushDelta(from);
        pushDelta(to);

        int res = INT_MIN;
        for (; from <= to; from = (from + 1) >> 1, to = (to - 1) >> 1) {
            if ((from & 1) != 0) {
                res = queryOperation(res, joinValueWithDelta(from));
            }
            if ((to & 1) == 0) {
                res = queryOperation(res, joinValueWithDelta(to));
            }
        }
        return res;
    }

    void modify(int from, int to, int d) {
        from = lower_bound(all(keys), from) - keys.begin();
        to =   upper_bound(all(keys), to) - keys.begin() - 1;
        if (from > to) {
            return;
        }
        from += n;
        to += n;
        pushDelta(from);
        pushDelta(to);
        int ta = -1;
        int tb = -1;
        for (; from <= to; from = (from + 1) >> 1, to = (to - 1) >> 1) {
            if ((from & 1) != 0) {
                delta[from] = joinDeltas(delta[from], d);
                if (ta == -1) {
                    ta = from;
                }
            }
            if ((to & 1) == 0) {
                delta[to] = joinDeltas(delta[to], d);
                if (tb == -1) {
                    tb = to;
                }
            }
        }
        for (int i = ta; i > 1; i >>= 1) {
            value[i >> 1] = queryOperation(joinValueWithDelta(i), joinValueWithDelta(i ^ 1));
        }
        for (int i = tb; i > 1; i >>= 1) {
            value[i >> 1] = queryOperation(joinValueWithDelta(i), joinValueWithDelta(i ^ 1));
        }
    }
};
