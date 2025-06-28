#include <bits/stdc++.h>
using namespace std;

const int N = 1000000;

int lp[N + 1];

vector<long long> primes;
vector <long long> sqprimes;

unordered_map<long long, long long> dp[N + 1];

inline long long get(long long m, int n) {
    int pos = min(n, (int)(upper_bound(all(sqprimes), m) - sqprimes.begin()) - 1);
    int add = n - pos;
    n = pos;
    if (m <= 1 || n == -1) {
        return m - add;
    }
    if (dp[n].count(m)) {
        return dp[n][m] - add;
    }

    return (dp[n][m] = get(m, n - 1) - get(m / primes[n], n - 1)) - add;
}

void prepare() {
    for (int i = 2; i <= N; ++i) {
        if (!lp[i]) {
            primes.push_back(i);
            sqprimes.push_back(i * 1ll * i);

            for (int j = i + i; j <= N; j += i) {
                lp[j] = 1;
            }
        }
    }
}

long long sqrt(long long x) {
    return sqrt(x * 1.0L) + 1e-9;
}

// https://stackoverflow.com/questions/19070911/feasible-implementation-of-a-prime-counting-function
long long get(long long x) {

    // naive version
    // return get(x, primes.size() - 1) + primes.size() - 1;

    if (x <= N) {
        return upper_bound(all(primes), x) - primes.begin();
    }

    int sqRoot = sqrt(x);
    int cbRoot = cbrt(x) + 1e-9;
    int fRoot = sqrt(sqRoot);

    int a = get(fRoot);
    int b = get(sqRoot);
    int c = get(cbRoot);

    long long sum = get(x, a - 1) + (b + a - 2ll) * (b - a + 1ll) / 2;
    for (int i = a; i < b; ++i) {
        long long w = x / primes[i];
        int lim = get(sqrt(w));
        sum -= get(w);
        if (i < c) {
            for (int j = i; j < lim; ++j) {
                sum = sum - get(w / primes[j]) + j;
            }
        }
    }

    return sum;
}

void solve(int _) {
    prepare();
    cout << get(1000000000000ll) << "\n";
}
