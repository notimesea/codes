#include <bits/stdc++.h>
using namespace std;

ll mulMOD(ll a, ll b, const ll MOD) {
    return __int128(a) * b % MOD;
}

ll powMOD(ll x, ll n, const ll MOD)
{
    ll res = 1;
    for (; n > 0; n >>= 1)
    {
        if (n & 1) res = mulMOD(res, x, MOD);
        x = mulMOD(x, x, MOD);
    }

    return res;
}

bool mr_test(ll n, int a, ll d, int s)
{
    ll x = powMOD(a, d, n);
    if (x == 1 || x == n - 1) return false;

    for (int r = 1; r < s; ++r)
    {
        x = mulMOD(x, x, n);
        if (x == n - 1) return false;
    }

    return true;
}

bool miller_rabin(ll n, int k = 50)
{
    if (n < 4) return n == 2 || n == 3;
    if (n % 2 == 0 || n % 3 == 0) return false;

    int s = __builtin_ctzll(n - 1);
    ll d = (n - 1) >> s;
    for (int it = 1; it <= k; ++it)
    {
        int a = 2 + rand() % (n - 3);
        if (mr_test(n, a, d, s)) return false;
    }

    return true;
}


ll any_divisor_of(ll n)
{
    ll d = n;
    for (ll c = 2; d == n; ++c)
    {    
        ll x = 2, y = 2, i = 2, k = 2;
        while (true)
        {
            x = (mulMOD(x, x, n) + c);
            if (x >= n)	x -= n;
            d = __gcd(abs(x - y), n);
            if (d > 1 && n % d == 0) break;
            if (i++ == k) y = x, k <<= 1;
        }
    }

    return d;
}

void factor(long long l, map <long long, int> &f) {
    for (ll p = 2; p <= 2000000 && l > 1; p++) {
        while (l % p == 0) {
            f[p]++;
            l /= p;
        }
    }

    if (l == 1) {
        return;
    }

    if (miller_rabin(l)) {
        f[l]++;
        return;
    }


    ll p = any_divisor_of(l);
    assert(p != l);
    assert(l % p == 0);

    f[p]++;
    f[l / p]++;
}
