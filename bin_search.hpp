#include <bits/stdc++.h>


struct Searcher {
    int *t;
    int n;
    int iters;
    size_t alignment;

    Searcher(const span<int> &a) {
        n = a.size();
        auto size = sizeof(int) * (n + 1);
        alignment = hardware_destructive_interference_size;
        size += alignment - size % alignment;
        t = (int *)(std::aligned_alloc(hardware_destructive_interference_size, size));
        t[0] = INT_MIN;
        iters = std::__lg(n + 1);

        int i = 0;
        eytzinger(a, 1, i);
    }

    ~Searcher() {
        free(t); 
    }

    void eytzinger(const span<int> &a, int k, int &i) {
        if (k <= a.size()) {
            eytzinger(a, 2 * k, i);
            t[k] = a[i++];
            eytzinger(a, 2 * k + 1, i);
        }
    }

    int lower_bound(int x) const {
        int k = 1;
        while (k <= n) {
            __builtin_prefetch(t + k * 16);
            k = 2 * k + (t[k] < x);
        }
        k >>= __builtin_ffs(~k);
        return t[k];
    }

    int lower_bound_faster(int x) const {
        int k = 1;

        for (int i = 0; i < iters; i++) {
            __builtin_prefetch(t + k * 16);
            k = 2 * k + (t[k] < x);
        }
            

        int *loc = (k <= n ? t + k : t);
        k = 2 * k + (*loc < x);

        k >>= __builtin_ffs(~k);

        return t[k];
    }
};
