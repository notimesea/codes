#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct miller_rabin {
    static ll mulmod(ll a, ll b, ll mod) {
        ll x = 0, y = a % mod;
        while (b > 0) {
            if (b % 2 == 1) {
                x = (x + y) % mod;
            }
            y = (y * 2) % mod;
            b /= 2;
        }
        return x % mod;
    }

    static ll modulo(ll base, ll exponent, ll mod) {
        ll x = 1;
        ll y = base;
        while (exponent > 0) {
            if (exponent % 2 == 1)
                x = (x * y) % mod;
            y = (y * y) % mod;
            exponent = exponent / 2;
        }
        return x % mod;
    }

    static bool check(ll p, int iteration = 100) {
        if (p <= 2) {
            return p == 2;
        }

        if (p % 2 == 0) {
            return false;
        }

        ll s = p - 1;
        while (s % 2 == 0) {
            s /= 2;
        }

        mt19937_64 g(p);
        auto dist = uniform_int_distribution<ll>(1, p);

        for (int i = 0; i < iteration; i++) {

            ll a = dist(g), temp = s;
            ll mod = modulo(a, temp, p);
            while (temp != p - 1 && mod != 1 && mod != p - 1) {
                mod = mulmod(mod, mod, p);
                temp *= 2;
            }
            if (mod != p - 1 && temp % 2 == 0) {
                return false;
            }
        }
        return true;
    }
};
