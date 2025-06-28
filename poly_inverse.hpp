// Polynomial inverse modulo prime.
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

inline ll mod_pow(ll a, ll e, ll mod) {
    ll r = 1;
    while (e) {
        if (e & 1) r = (__int128)r * a % mod;
        a = (__int128)a * a % mod;
        e >>= 1;
    }
    return r;
}

inline ll mod_inv(ll a, ll mod) {
    return mod_pow(a, mod - 2, mod);
}

static vector<int> multiply(const vector<int>& a, const vector<int>& b, int mod) {
    vector<int> res(a.size() + b.size() - 1);
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < b.size(); ++j) {
            res[i + j] = (res[i + j] + (ll)a[i] * b[j]) % mod;
        }
    }
    return res;
}

// Returns polynomial `b` such that a(x) * b(x) = 1 (mod x^n)
inline vector<int> poly_inverse(const vector<int>& a, int mod) {
    assert(!a.empty() && a[0] % mod != 0);
    int n = (int)a.size();
    vector<int> res(1, (int)mod_inv((a[0]%mod+mod)%mod, mod));
    int m = 1;
    while (m < n) {
        m <<= 1;
        vector<int> pref(min(m, n));
        for (int i = 0; i < (int)pref.size(); ++i) pref[i] = a[i] % mod;
        vector<int> tmp = multiply(res, pref, mod);
        tmp.resize(m);
        for (int i = 0; i < m; ++i) {
            ll val = (2LL * res[i % res.size()] - (i < (int)tmp.size() ? tmp[i] : 0)) % mod;
            if (val < 0) val += mod;
            if (i < (int)res.size()) res[i] = (int)val;
            else res.push_back((int)val);
        }
    }
    res.resize(n);
    return res;
}

