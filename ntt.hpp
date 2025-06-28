#include <bits/stdc++.h>
using namespace std;

const ll mod = 998244353;
ll root = 3;
ll root_1 = 0;
const ll root_pw = 1<<20;

void pre() {
    while (true) {
        if (pw(root, root_pw, mod) == 1 && pw(root, root_pw / 2, mod) == mod - 1) {
            break;
        }
        ++root;
    }
    cerr << root << endl;
    root_1 = inv(root, mod);
}

void fft (vector<ll> & a, bool invert) {
    int n = (int) a.size();

    for (int i=1, j=0; i<n; ++i) {
        int bit = n >> 1;
        for (; j>=bit; bit>>=1)
            j -= bit;
        j += bit;
        if (i < j)
            swap (a[i], a[j]);
    }

    for (int len=2; len<=n; len<<=1) {
        ll wlen = invert ? root_1 : root;
        for (int i=len; i<root_pw; i<<=1)
            wlen = ll (wlen * 1ll * wlen % mod);
        for (int i=0; i<n; i+=len) {
            ll w = 1;
            for (int j=0; j<len/2; ++j) {
                ll u = a[i+j],  v = ll (a[i+j+len/2] * 1ll * w % mod);
                a[i+j] = u+v < mod ? u+v : u+v-mod;
                a[i+j+len/2] = u-v >= 0 ? u-v : u-v+mod;
                w = ll (w * 1ll * wlen % mod);
            }
        }
    }
    if (invert) {
        ll nrev = inv(1ll * n, mod);
        for (int i=0; i<n; ++i)
            a[i] = int (a[i] * 1ll * nrev % mod);
    }
}
