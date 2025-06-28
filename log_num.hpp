// Number representation in log space.
#include <bits/stdc++.h>

template <typename T>
struct Num {
    T lv;

    Num() : lv(-numeric_limits<T>::lowest()) {}

    Num(const T &v) {
        if (v == 0) {
            *this = Num();
        } else {
            lv = log(v);
        }
    }

    static Num build(ld value) {
        Num res;
        res.lv = value;
        return res;
    }

    bool isZero() const {
        return lv == -numeric_limits<T>::lowest();
    }

    T value() const {
        if (isZero()) {
            return 0;
        }

        return exp(lv);
    }

    Num operator*(const Num &r) const {
        if (isZero() || r.isZero()) return Num();
        return build(lv + r.lv);
    }

    Num operator/(const Num &r) const {
        if (isZero()) return Num();
        assert(!r.isZero());

        return build(lv - r.lv);
    }

    Num operator+(const Num &r) const {
        if (isZero()) return r;
        if (r.isZero()) return *this;

        T m = max(lv, r.lv);
        return build(m + log(exp(lv - m) + exp(r.lv - m)));
    }

    Num operator-(const Num &r) const {
        if (isZero()) return r;
        if (r.isZero()) return *this;

        T m = max(lv, r.lv);
        return build(m + log(exp(lv - m) - exp(r.lv - m)));
    }
};
