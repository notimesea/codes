// Rolling hash of string suffixes. Requires global mod.
#include <bits/stdc++.h>


string t;
vector <long long> hashes;
vector <long long> powers;
long long mod = 1000000009;

long long getHash(int pos, int len) {
    return (hashes[pos + len] - hashes[pos] * powers[len] % mod + mod) % mod;
}

int lcp(int a, int b) {
    int l = 0, r = min(t.length() - a, t.length() - b);
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (getHash(a, mid) == getHash(b, mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return l;
}

bool compare(int a, int b) {
    int len = lcp(a, b);
    return t[a + len] < t[b + len];
}
