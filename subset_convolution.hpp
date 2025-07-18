//
// Created by Evgeny Savinov on 08/09/16.
//

#include <bits/stdc++.h>

using namespace std;


template<class T>
void mobius(vector<T> &f) {
    int n = __builtin_ctz(f.size());
    int N = f.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < N; ++j) {
            if (!(j & (1 << i))) f[j ^ (1 << i)] += f[j];
        }
    }
}

template<class T>
void inverse_mobius(vector<T> &f) {
    int n = __builtin_ctz(f.size());
    int N = f.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < N; ++j) {
            if (!(j & (1 << i))) f[j ^ (1 << i)] -= f[j];
        }
        continue;
    }
}

template <class T>
vector<T> stupid_convolution(const vector<T> &a, const vector<T> &b) {
    int N = a.size();
    vector<T> c(N);

    for (int i = 0; i < N; ++i) {
        for (int j = i; j < N; j = (j + 1) | i) {
            c[j] += a[i] * b[i ^ j];
        }
    }
    return c;
}

template<class T>
vector<T> convolution(const vector<T> &a, const vector<T> &b) {
    int N = a.size();
    int n = __builtin_ctz(N);


    // Stupid is faster when n < 16
    if (n < 16) return stupid_convolution(a, b);

    vector<vector<T> > fa(n + 1, vector<T>(N));
    vector<vector<T> > fb(n + 1, vector<T>(N));
    vector<vector<T> > fc(n + 1, vector<T>(N));

    for (int i = 0; i < N; ++i) {
        fa[__builtin_popcount(i)][i] = a[i];
        fb[__builtin_popcount(i)][i] = b[i];
    }

    for (int i = 0; i <= n; ++i) {
        mobius(fa[i]);
        mobius(fb[i]);
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j + i <= n; ++j) {
            for (int k = 0; k < N; ++k) {
                fc[i + j][k] += fa[i][k] * fb[j][k];
            }
        }
    }

    for (int i = 0; i <= n; ++i) {
        inverse_mobius(fc[i]);
    }

    vector<T> c(N);

    for (int i = 0; i < N; ++i) {
        c[i] = fc[__builtin_popcount(i)][i];
    }

    return c;
}

