// HyperLogLog cardinality estimator.
#include <bits/stdc++.h>

template <int np_ = 14>
struct hll {
    uint8_t data[1 << np_];

    void add(uint64_t h) {
        const std::uint32_t index(h >> (64u - np_)), lzt(__builtin_clzll(h << np_) + 1);
        if(data[index] < lzt) data[index] = lzt;
    }

    long long sum() const {
        long double s = 0;
        for (int i = 0; i < (1 << np_); ++i) {
            s += 1.0L / (1ll << data[i]);
        }
        double alpha = 0.7213 / (1 + 1.079/(1 << np_));

        return alpha * (1ll << np_) * (1ll << np_) / s;
    }
};
