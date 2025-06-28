// Fenwick tree for prefix sums.
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;

// Lightweight Fenwick Tree (Binary Indexed Tree)
// Supports point updates and prefix sum queries.
template <class T>
struct fenwick {
    // internal array of size n
    vector <T> data;

    // create tree for n elements initialized with zeros
    fenwick(int n) {
        data.resize(n);
    }
    
    // add "val" to position "pos"
    void add(int pos, T val) {
        for (; pos < data.size(); pos |= pos + 1) {
            data[pos] = data[pos] + val;
        }
    }
    
    // get sum of range [0, r]
    T get(int r) const {
        T res{};
        for (; r >= 0; r &= r + 1, --r) {
            res = res + data[r];
        }
        return res;
    }
};
