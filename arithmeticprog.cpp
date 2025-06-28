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
long long half = (mod + 1) / 2;

const int N = 1 << 20;

long long add[N], mul[N], sq[N];
int sz;


void Update(int r, long long add_add, long long mul_add, long long sq_add) {
    for (; r < sz; r |= r + 1) {
        add[r] += add_add;
        add[r] %= mod;
        mul[r] += mul_add;
        mul[r] %= mod;
        sq[r] += sq_add;
        sq[r] %= mod;
    }
}

long long get(long long r) {
    long long R = r;
    long long res_add = 0, res_mul = 0, res_sq = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1) {
        res_add += add[r];
        res_mul += mul[r];
        res_sq += sq[r];
    }
    res_add %= mod;
    res_mul %= mod;
    res_sq %= mod;

    return (res_add + res_mul * R % mod + res_sq * R % mod * (R - 1) % mod * half % mod) % mod;
}

void update(int l, int r, long long A, long long B) {
    if (l > r) return;
    Update(l, (-B * (l - 1) % mod + A * l % mod * (l - 1) % mod * half % mod) % mod, (B - A * (l - 1) % mod) % mod,
           A % mod);
    Update(r, (B * r % mod + A * r % mod * (r + 1) % mod * half % mod - A * r % mod * l % mod) % mod,
           (-B + A * (l - 1)) % mod, (-A) % mod);
}

long long get(int l, int r) {
    return ((get(r) - get(l - 1)) % mod + mod) % mod;
}

long long a[N];

void update2(int l, int r, long long mul, long long add) {
    long long cur = 0;
    for (int i = l; i <= r; ++i) {
        a[i] += add + cur;
        a[i] %= mod;
        cur += mul;
        cur %= mod;
    }
}

long long get2(int l, int r) {
    long long res = 0;
    for (int i = l; i <= r; ++i)
        res += a[i];
    return (res % mod + mod) % mod;
}

int n, m, q;

int pos(int x, int y) {
    return y - x + n - 1;
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

    n = nxt(), m = nxt(), q = nxt();

    sz = pos(0, m - 1) + 1;

    char buf[10];

    while (q--) {
        scanf("%s", buf);
        if (buf[1] == 'c') {
            int col = nxt() - 1;
            long long delta = nxt();

            int dmin = pos(n - 1, col);
            int dmax = pos(0, col);

            update(dmin, dmax, -delta, delta * n % mod);
        }
        if (buf[1] == 'r') {
            int row = nxt() - 1;
            long long delta = nxt();
            int dmin = pos(row, 0);
            int dmax = pos(row, m - 1);

            update(dmin, dmax, delta, delta);
        }

        if (buf[1] == 's') {
            int r1 = nxt() - 1, c1 = nxt() - 1;
            int r2 = nxt() - 1, c2 = nxt() - 1;


            long long delta = nxt();

            if ((r1 == r2 || c1 == c2)) {
                int d1 = pos(r1, c1);
                int d2 = pos(r2, c2);
                if (d1 > d2) {
                    swap(d1, d2);
                }
                update(d1, d2, 0, delta);
                continue;
            }

            int width = min(r2 - r1 + 1, c2 - c1 + 1);

            int d1 = pos(r2, c1);
            int d2 = pos(r1, c1);
            int d3 = pos(r2, c2);
            int d4 = pos(r1, c2);

            if (d2 > d3) {
                swap(d2, d3);
            }
            assert(d1 <= d2 && d2 <= d3 && d3 <= d4);
            //cerr << r1 << " " << c1 << " " << r2 << " " << c2 << "\n";
            //cerr << d1 << " " << d2 << " " << d3 << " " << d4 << "\n";
            //cerr << width << "\n";
            assert(d2 - d1 + 1 == width);
            assert(d4 - d3 + 1 == width);
            update(d1, d2 - 1, delta, delta);
            update(d2, d3 - 1, 0, delta * width % mod);
            update(d3, d4, (-delta) % mod, delta * width % mod);
        }

        if (buf[1] == 'd') {
            int dmin = nxt() - 1;
            int dmax = nxt() - 1;

            cout << get(dmin, dmax) << "\n";
        }
    }


#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
} 
