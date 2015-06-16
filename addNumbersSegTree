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
const int N = 1 << 17;
int color[N << 1];
int cnt[N << 1][2];

void push(int v) {
    if (color[v] != -1) {
        color[v + v] = color[v + v + 1] = color[v];
        color[v] = -1;
    }
}

int get(int v, int c) {
    if (color[v] == -1) {
        return cnt[v][c];
    }
    if (color[v] == c) {
        return cnt[v][0] + cnt[v][1];
    } else {
        return 0;
    }
}

void update(int v) {
    for (int i = 0; i < 2; ++i) {
        cnt[v][i] = get(v + v, i) + get(v + v + 1, i);
    }
}


int find2(int v, int tl, int tr, int c) {
    if (tl == tr) {
        return tl;
    }
    push(v);
    int tm = (tl + tr) / 2;
    int res;
    if (get(v + v, c)) {
        res = find2(v + v, tl, tm, c);
    } else {
        res = find2(v + v + 1, tm + 1, tr, c);
    }
    update(v);
    return res;
}

int find(int v, int tl, int tr, int pos, int c) {
    if (tl == tr) {
        return get(v, c) ? tl : -1;
    }
    push(v);
    int res;
    int tm = (tl + tr) / 2;

    if (pos > tm) {
        res = find(v + v + 1, tm + 1, tr, pos, c);
    } else {
        res = find(v + v, tl, tm, pos, c);
        if (res == -1 && get(v + v + 1, c)) {
            res = find2(v + v + 1, tm + 1, tr, c);
        }
    }
    update(v);
    return res;
}


void recolor(int v, int tl, int tr, int l, int r, int c) {
    if (l > r) return;
    if (tl == l && tr == r) {
        color[v] = c;
        return;
    }
    push(v);

    int tm = (tl + tr) / 2;

    recolor(v + v, tl, tm, l, min(tm, r), c);
    recolor(v + v + 1, tm + 1, tr, max(tm + 1, l), r, c);

    update(v);
}

int test(int v, int tl, int tr, int pos) {
    if (tl == tr) {
        return get(v, 1);
    }
    push(v);
    int tm = (tl + tr) / 2;
    int res;
    if (pos <= tm) {
        res = test(v + v, tl, tm, pos);
    } else {
        res = test(v + v + 1, tm + 1, tr, pos);
    }
    update(v);
    return res;
}

void add(int pos, int delta) {
    if (delta == 0) return;
    if (delta == 1) {
        int p = find(1, 0, N - 1, pos, 0);
        recolor(1, 0, N - 1, p, p, 1);
        recolor(1, 0, N - 1, pos, p - 1, 0);
    } else {
        int p = find(1, 0, N - 1, pos, 1);
        recolor(1, 0, N - 1, p, p, 0);
        recolor(1, 0, N - 1, pos, p - 1, 1);
    }
}

void build(int v, int tl, int tr) {
    color[v] = -1;
    if (tl == tr) {
        cnt[v][0] = 1;
        return;
    }
    int tm = (tl + tr) / 2;
    build(v + v, tl, tm);
    build(v + v + 1, tm + 1, tr);
    update(v);
}

void print(int n) {
    for (int i = 0; i < n; ++i) {
        cerr << test(1, 0, N - 1, i);
    }
    cerr << "\n";
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

    int n = nxt(), q = nxt();

    string A, B;
    cin >> A >> B;

    reverse(all(A));
    reverse(all(B));

    build(1, 0, N - 1);

    for (int i = 0; i < n; ++i) {
        add(i, A[i] - '0');
        add(i, B[i] - '0');
    }
    //print(n + 1);

    while (q--) {
        char s[10];
        scanf("%s", s);
        if (s[0] == 'g') {
            int pos = nxt();
            if (pos >= N) {
                cout << "0";
            } else {
                cout << test(1, 0, N - 1, pos);
            }
        } else {
            int pos = nxt();
            char x = nxt() + '0';
            if (s[4] == 'a') {
                add(pos, x - A[pos]);
                A[pos] = x;
            } else {
                add(pos, x - B[pos]);
                B[pos] = x;
            }
        }
        //print(n + 1);
    }
    cout << "\n";


#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
}   
