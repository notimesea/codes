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
typedef long long ll;
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

typedef vector <vector <long long> > matrix;

const int N = 1000000;

int lp[N + 1];

vector <long long> primes;

unordered_map <long long, long long> dp[N];

long long get(long long m, int n) {
    long long z = (long long) (sqrt(m) + 1e-9);
    int pos = min(n, (int)(upper_bound(all(primes), z) - primes.begin()) - 1);
    long long add = n - pos;
    n = pos;
    if (m <= 1) {
        return m - add;
    }
    if (n == -1) {
        return m - add;
    }
    if (dp[n].count(m)) {
        return dp[n][m] - add;
    }

    return (dp[n][m] = get(m, n - 1) - get(m / primes[n], n - 1)) - add;
}

long long get(long long x) {
    return get(x, (int)primes.size() - 1) + (int)primes.size() - 1;
}

unordered_map <long long, long long> dp2[N];
vector <long long> primeSum;

long long mod = 1000000123;
long long r2 = (mod + 1) / 2;

long long get2(long long m, int n) {
    long long z = (long long) (sqrt(m) + 1e-9);
    int pos = min(n, (int)(upper_bound(all(primes), z) - primes.begin()) - 1);
    long long add = primeSum[n + 1] - primeSum[pos + 1];
    n = pos;
    if (m <= 1 || n == -1) {
        return (m * (m + 1) % mod * r2 % mod - add) % mod;
    }
    if (dp2[n].count(m)) {
        return (dp2[n][m] - add) % mod;
    }

    return ((dp2[n][m] = (get2(m, n - 1) - primes[n] * get2(m / primes[n], n - 1)) % mod) - add) % mod;
}

long long get2(long long x) {
    return (get2(x, (int)primes.size() - 1) + primeSum[primes.size()] - 1) % mod;
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


    for (int i = 2; i <= N; ++i) {
        if (!lp[i]) {
            primes.push_back(i);
            for (int j = i + i; j <= N; j += i) {
                lp[j] = 1;
            }
        }
    }
    primeSum.resize(primes.size() + 1);
    primeSum[0] = 0;
    for (int i = 0; i < (int)primes.size(); ++i) {
        primeSum[i + 1] = (primeSum[i] + primes[i]) % mod;
    }
//    for (int i = 0; i < primes.size(); ++i) {
//        //cerr << primes[i] << " " << get2(primes[i]) << " " << ((primes[i] * (primes[i] + 1)) / 2 - primeSum[i + 1]) << "\n";
////        assert((get2(primes[i]) + mod) % mod == (primeSum[i + 1] + mod) % mod);
////        cerr << i << "\n";
//    }
    

    auto start = std::chrono::high_resolution_clock::now();

    long long n = 1000000000000ll;


    long long x = 0;
    for (int i = 0; i < (int)primes.size(); ++i) {
        long long p1 = primes[i];
        if (p1 * p1 * p1 > n) break;
        for (long long j = i + 1; j < primes.size(); ++j) {
            long long p2 = primes[j];
            if (p1 * p2 * p2 > n) break;
            long long r = n / p1 / p2;
            x += get(r) - get(p2);
        }
    }

    for (int i = 0; i < (int)primes.size(); ++i) {
        long long p1 = primes[i];
        if (p1 * p1 * p1 > n) break;
        long long r = n / p1 / p1 / p1;
        x += get(r);
        x -= p1 <= r;
    }

    for (int i = 0; i < (int)primes.size(); ++i) {
        long long p1 = primes[i];
        if (p1 * p1 * p1 * p1 * p1 * p1 * p1 > n) break;
        x += 1;
    }


    cout << x << "\n";
    auto finish = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() << "ms\n";


#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
}
