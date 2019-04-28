const long long mod = 1000000007;

template <int N, int M>
struct mat {
    long long data[N * M]{0};

    long long &get(int u, int v) {
        return data[u * M + v];
    }

    const long long &get(int u, int v) const {
        return data[u * M + v];
    }
};

template <int N, int M, int K> mat<N, K> mul(const mat<N, M> &l, const mat <M, K> &r) {
    mat <N, K> res;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < K; ++j) {
            for (int k = 0; k < M; ++k) {
                res.get(i, j) += l.get(i, k) * r.get(k, j);
                res.get(i, j) %= mod;
            }
        }
    }
    return res;
}

template <int N> mat <N, 1> pw(mat <N, N> a, mat <N, 1> b, long long n) {
    while (n) {
        if (n & 1ll) {
            b = mul(a, b);
        }
        n >>= 1;
        a = mul(a, a);
    }
    return b;
}
