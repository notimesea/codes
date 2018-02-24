//
// Created by Evgeny Savinov on 09/01/2017.
//

#include <bits/stdc++.h>

#pragma GCC optimize ("O3")

#define clr(x) memset((x), 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define forn(i, n) for(int i = 0; i < (int)(n); ++i)
#define ford(i, n) for(int i = (int)(n) - 1; i >= 0; --i)
#define for1(i, n) for(int i = 1; i <= (int)(n); ++i)


using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
//typedef pair<long long, long long> pii;
typedef vector<long long> vll;
typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef int itn;
typedef unsigned int uint;

const ld PI = 3.1415926535897932384626433832795L;

template<class T>
bool uin(T &, const T &);

template<class T>
bool uax(T &, const T &);

template<class T>
T gcd(T, T);

template<class T>
T lcm(T, T);

template<class _T>
inline string tostr(const _T &);

template<typename T>
void input(T &);

//template <typename T = int>
class range {
    using type = int;
public:
    class iterator {
        friend class range;

    public:
        using difference_type = range::type;
        using value_type = range::type;
        using pointer = const range::type *;
        using reference = const range::type &;
        using iterator_category = std::random_access_iterator_tag;

        value_type operator*() const { return i_; }

        const iterator &operator++() {
            ++i_;
            return *this;
        }

        iterator operator++(int) {
            iterator copy(*this);
            ++i_;
            return copy;
        }

        const iterator &operator--() {
            --i_;
            return *this;
        }

        iterator operator--(int) {
            iterator copy(*this);
            --i_;
            return copy;
        }

        difference_type operator-(const iterator &other) const { return i_ - other.i_; }

        iterator operator+(const difference_type &delta) const { return iterator(i_ + delta); }

        iterator &operator+=(const difference_type &delta) {
            i_ += delta;
            return *this;
        }

        iterator operator-(const difference_type &delta) const { return iterator(i_ - delta); }

        iterator &operator-=(const difference_type &delta) {
            i_ -= delta;
            return *this;
        }

        bool operator==(const iterator &other) const { return i_ == other.i_; }

        bool operator!=(const iterator &other) const { return i_ != other.i_; }

    protected:
        iterator(const value_type &start) : i_(start) {}

    private:
        value_type i_;
    };

    iterator begin() const { return begin_; }

    iterator end() const { return end_; }

    range(const type &begin, const type &end) : begin_(begin), end_(end) {}

    range(const type &end) : begin_(0), end_(end) {}

private:
    iterator begin_;
    iterator end_;
};

template<typename T = long long>
T nxt();

bool checkp(long long);

template<typename T>
T pw(T a, T n, T p);

template<typename T>
T inv(T a, T p);

template<class _T>
_T sqr(const _T &x);

class range;

mt19937_64 gen;

int TTT;

const ll mod = 1000000007;

void pre() {}


int val[1 << 20];
int add[1 << 20];

void push(int v) {
    add[v + v] += add[v];
    add[v + v + 1] += add[v];
    add[v] = 0;
}

void update(int v, int tl, int tr, int l, int r, int x) {
    if (l >= r) return;
    if (tl == l && tr == r) {
        add[v] += x;
        return;
    }
    push(v);
    int tm = (tl + tr) / 2;

    update(v + v, tl, tm, l, min(r, tm), x);
    update(v + v + 1, tm, tr, max(tm, l), r, x);

    val[v] = max(val[v + v] + add[v + v], val[v + v + 1] + add[v + v + 1]);
}

void get(int v, int tl, int tr, vector<int> &pos) {
    if (val[v] + add[v] == 0) return;

    if (tr - tl == 1) {
        pos.push_back(tl);
        return;
    }

    push(v);
    int tm = (tl + tr) / 2;

    get(v + v, tl, tm, pos);
    get(v + v + 1, tm, tr, pos);

    val[v] = max(val[v + v] + add[v + v], val[v + v + 1] + add[v + v + 1]);
}

const int N = 300001;

struct Event {
    int l;
    int r;
    int delta;
};

vector<Event> e[N + 1];


const int maxn = N;

vector<int> g[maxn];
int n1, n2, m, test = 0;
int c[maxn], r[maxn], l1[maxn], l2[maxn], ok[maxn], step = 100;
int q[maxn], qs, qz;


bool dfs(int u) {
    c[u] = step;
    for (int i = 0; i < (int) g[u].size(); i++) {
        int to = g[u][i];
        if (l2[to] != l1[u] + 1)
            continue;
        if (r[to] == -1 || (c[r[to]] != step && dfs(r[to]) && l1[r[to]] == l1[u] + 2)) {
            r[to] = u;
            return true;
        }
    }
    return false;
}

int cc[maxn];

bool dfs2(int u) {
    c[u] = step;
    for (int i = 0; i < (int) g[u].size(); i++) {
        int to = g[u][i];
        if (r[to] != -1 && c[r[to]] != step) {
            cc[to] = step;
            dfs2(r[to]);
        }
    }
    return false;
}

void bfs() {
    qs = qz = 0;
    memset(c, 0, sizeof(c[0]) * n1);
    memset(l1, -1, sizeof(l1[0]) * n1);
    memset(l2, -1, sizeof(l2[0]) * n2);
    for (int i = 0; i < n1; i++)
        if (!ok[i])
            q[qs + qz++] = i, l1[i] = 1, c[i] = 1;
    while (qz > 0) {
        int u = q[qs++];
        qz--;
        for (int i = 0; i < (int) g[u].size(); i++)
            if (l2[g[u][i]] == -1) {
                l2[g[u][i]] = l1[u] + 1;
                if (r[g[u][i]] != -1 && c[r[g[u][i]]] == 0) {
                    c[r[g[u][i]]] = 1;
                    l1[r[g[u][i]]] = l1[u] + 2;
                    q[qs + qz++] = r[g[u][i]];
                }
            }
    }
}

void solve(int test) {

    int n = nxt();

    forn(i, n) {
        int x1 = nxt();
        int y1 = nxt();

        int x2 = nxt() + 1;
        int y2 = nxt() + 1;

        e[x1].pb(Event{y1, y2, 1});
        e[x2].pb(Event{y1, y2, -1});
        
    }

    for (int i = 0; i < N; ++i) {
        for (auto ee : e[i]) {

            update(1, 0, N, ee.l, ee.r, ee.delta);
        }
        vector<int> p;
        get(1, 0, N, p);
        for (int x : p) {

            g[i].pb(x);
        }
    }

    n1 = n2 = N;

    memset(r, -1, sizeof(r[0]) * n2);
    memset(ok, 0, sizeof(ok[0]) * n1);
    bool good = true, ans = true;
    while (good)
    {
        good = false;
        bfs();
//      memset(c, 0, sizeof(c[0]) * n1);
        step++;
        for (int i = 0; i < n1; i++)
            if (l1[i] == 1 && c[i] != step && dfs(i))
                ok[i] = true, good = true;
    }

    step++;
    int M = 0;
    for (int i = 0; i < n1; i++)
        if (!ok[i]) {
            dfs2(i);
        } else {
            M += 1;
        }

    vi rows, cols;
    for (int i = 0; i < n1; ++i) {
        if (c[i] != step) rows.pb(i);
        if (cc[i] == step) cols.pb(i);
    }
    assert(M == rows.size() + cols.size());
    cout << M << "\n";

    cout << rows.size() << "\n";
    for (int x : rows) cout << x << " ";
    cout << "\n";

    cout << cols.size() << "\n";
    for (int x : cols) cout << x << " ";
    cout << "\n";
}

#undef int

int main(int argc, char **argv) {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
#else
#define fname "sequence"
    //freopen(fname".in", "r", stdin);
    //freopen(fname".out", "w", stdout);
#endif
    pre();
    ::TTT = 1;
#ifdef LOCAL
#else
#endif

    for (int test = 1; test <= ::TTT; ++test) {
        solve(test);
    }

#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
}


template<typename T>
T gcd(T x, T y) {
    while (y > 0) {
        x %= y;
        swap(x, y);
    }
    return x;
}

template<class T>
T lcm(T a, T b) {
    return a / gcd(a, b) * b;
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


template<typename T>
inline void input(T &a) {
    static int ed;
    a = 0;
    while (!isdigit(ed = getchar()) && ed != '-') {}
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

template<typename T = long long>
inline T nxt() {
    T res;
    input(res);
    return res;
}

void myassert(bool v) {
    assert(v);
//cout << "FAIL\n";
//exit(0);
}


bool checkp(long long v) {
    if (v < 2) return false;
    for (long long i = 2; i * i <= v; ++i) {
        if (v % i == 0) {
            return false;
        }
    }
    return true;
}

template<typename T>
T pw(T a, T n, T m) {
    T res = 1;
    while (n) {
        if (n & 1) {
            res = res * a % m;
        }
        a = a * a % m;
        n >>= 1;
    }
    return res;
}

template<typename T>
T inv(T a, T p) {
    T res = 1;
    while (a > 1) {
        res = res * (p - p / a) % p;
        a = p % a;
    }
    return res;
}


template<class T>
bool uin(T &a, const T &b) {
    if (b < a) {
        a = b;
        return true;
    }
    return false;
}

template<class T>
bool uax(T &a, const T &b) {
    if (b > a) {
        a = b;
        return true;
    }
    return false;
}
