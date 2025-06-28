//timus 1816

#include <bits/stdc++.h>

#define clr(x) memset((x), 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define mp make_pair
#define in(x) int (x); input((x));
#define x first
#define y second
typedef int itn;

#define next next12345
#define prev prev12345
#define left lefdsf232
#define right rig43783
#define x1 x12345
#define y1 y12345

using namespace std;

template<typename T>
T gcd(T x, T y) {
    while (y > 0) {
        x %= y;
        swap(x, y);
    }
    return x;
}

template<class _T>
inline _T sqr(const _T &x) {
    return x * x;
}

template<class _T>
inline string tostr(const _T &a) {
    ostringstream os("");
    os << a;
    return os.str();
}

typedef long double ld;
using ll = long long;
typedef unsigned long long ull;
typedef pair<int, int> PII;
const long double PI = 3.1415926535897932384626433832795L;

template<typename T>
inline void input(T &a) {
    static int ed;
    a = 0;
    while (!isdigit(ed = getchar()) && ed != '-') { }
    char neg = 0;
    if (ed == '-') {
        neg = 1;
        ed = getchar();
    }
    while (isdigit(ed)) {
        a = 10 * a + ed - '0';
        ed = getchar();
    }
    if (neg) a = -a;
}

template<typename T = int>
inline T nxt() {
    T res;
    input(res);
    return res;
}

mt19937 generator;

long long mod = 1000000007;

void fib(unsigned long long n, long long &x, long long &y) {
    if (n == 1) {
        x = 0, y = 1;
        return;
    }
    if (n & 1ull) {
        fib(n - 1, y, x);
        y += x;
        y %= mod;
    } else {
        long long a, b;
        fib(n / 2, a, b);
        x = (a * a + b * b) % mod;
        y = (2 * a + b) * b % mod;
    }
}

long long pw(long long a, long long n) {
    long long res = 1;
    while (n) {
        if (n & 1ull) {
            res = res * a % mod;
        }
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

map <long long, int> dp;

map <long long, vector <long long> > divisors;

vector <long long> & getDivs(long long x) {
    if (divisors.count(x)) {
        return divisors[x];
    }
    vector <long long> divs;
    long long d;

    for (d = 1; d * d < x; ++d) {
        if (x % d == 0) {
            divs.push_back(d);
            divs.push_back(x / d);
        }
    }
    if (d * d == x) {
        divs.push_back(d);
    }
    return divisors[x] = divs;
}

int mu(long long x) {
    if (x == 1) {
        return 1;
    }
    if (dp.count(x)) {
        return dp[x];
    }
    vector <long long> & divs = getDivs(x);

    int res = 0;

    for (long long d : divs) {
        if (d == x) {
            continue;
        }
        res -= mu(d);
    }

    return dp[x] = res;
}


long long get(long long r, long long g, long long x) {
    vector <long long> & divs = getDivs(x);

    long long res = 0;

    for (long long d : divs) {
        if (d % g == 0) {
            res += r / d * mu(d / g);
        }
    }

    return res;
}

long long get2(long long r, long long g, long long x) {
    long long res = 0;
    for (long long i = 1; i <= r; ++i) {
        if (gcd(i, x) == g) {
            res += 1;
        }
    }
    return res;
}

map <long long, long double> res;

long long magic = 1000000000000000000ll;

long double solve(long long n) {
    if (res.count(n)) {
        return res[n];
    }
    const auto & divs = getDivs(n);
    if (divs.size() == 2) {
        return res[n] = 0;
    }

    long double l = 1;
    long double r = 1;

    for (long long d : divs) {
        if (d == 1 || d == n) {
            l -= (long double)get(magic, d, n) / magic;
            continue;
        }
        r += (long double)get(magic, d, n) / magic * (solve(d) + solve(n / d));
    }

    return res[n] = r / l;
}

int main() {
    //#define int long
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
#define fname "race"
    //freopen(fname".in", "r", stdin);
    //freopen(fname".out", "w", stdout);
#endif

//    for (int i = 1; i <= 50; ++i) {
//        for (int j = 1; j <= 50; ++j) {
//            for (int k = j; k <= 50; ++k) {
//                if (k % j != 0) continue;
//                cerr << i << " " << j << " " << k << " " << get(i, j, k) << " " << get2(i, j, k) << "\n";
//                assert(get(i, j, k) == get2(i, j, k));
//            }
//        }
//    }

    int n = nxt();

    cout << setprecision(10) << fixed;
    cout << solve(n) << "\n";


#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
}   
