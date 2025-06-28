// sqrt-decomposition with range sum/update.
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;

template <int K>
struct add_sum {
    vector <long long> block_pref_sum;
    vector <long long> block_sum;

    add_sum(int n) {
        block_pref_sum.resize(n);
        block_sum.resize(n / K + 2);
    }

    void add(int pos, long long val) {
        int block = pos / K;
        for (int b = block + 1; b < block_sum.size(); ++b) {
            block_sum[b] += val;
        }

        int block_end = block * K + K;
        for (; pos < block_end && pos < block_pref_sum.size(); ++pos) block_pref_sum[pos] += val;
    }

    long long get(int r) {
        if (r < 0) return 0;

        int block = r / K;
        return block_sum[block] + block_pref_sum[r];
    }

    long long get(int l, int r) {
        r = min(r, (int)block_pref_sum.size());
        return get(r - 1) - get(l - 1);
    }
};
