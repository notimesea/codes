#include <bits/stdc++.h>

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
typedef pair<int, int> pii;
typedef vector<long long> vll;
typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef int itn;

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

template<typename T = long long>
T nxt();

bool checkp(long long);

template<typename T>
T pw(T a, T n, T p);

template<typename T>
T inv(T a, T p);

void pre() {

}

vi vset;
vector <vector <int> > M;

ll T0[1000], T1[1000];

int S;

ll counter = 0;

ll rec(ll mask, ll TRUE, ll FALSE) {
    ll res = 0;

    ll mul = 1;

    while (mask) {
        int bit = __builtin_ctzll(mask);
        int i = bit;
        ll T = T0[2 * i] | T0[2 * i + 1] | T1[2 * i] | T1[2 * i + 1];
        T ^= 1ll << i;
        if (!(T & mask)) {
            mask ^= 1ll << i;
            TRUE ^= 1ll << i;
            mul *= 2;
        } else {
            break;
        }
    }

    if (!mask) {
        return mul;
    }
    int bit = __builtin_ctzll(mask);
    forn(x, 2) {
        ll nmask = mask;
        ll nTRUE = TRUE;
        ll nFALSE = FALSE;

        ll toSET0 = T0[2 * bit + x];
        ll toSET1 = T1[2 * bit + x];

        if (toSET0 & toSET1) {
            continue;
        }
        ll r0 = toSET0 & mask;
        ll r1 = toSET1 & mask;
        ll rem = r0 | r1;
        if (r0 & TRUE) {
            continue;
        }
        if (r1 & FALSE) {
            continue;
        }
        nmask ^= rem;
        nTRUE |= r1;
        nFALSE |= r0;

        res += rec(nmask, nTRUE, nFALSE);
    }
    
    return res * mul;
}

int p[1000];


int get(int v) {
    if (p[v] != v) {
        return p[v] = get(p[v]);
    } else {
        return p[v];
    }
}

void unite(int a, int b) {
    a = get(a);
    b = get(b);
    if (a == b) {
        return;
    }
    p[a] = b;
}

void solve(int test) {
    int n = nxt();
    int m = nxt();

    int d[n * 2][n * 2];
    clr(d);

    forn(i, 2*n) d[i][i] = 1;

    forn(i, m) {
        int u, v;

        u = -nxt();
        v = nxt();

        int a, b;



        if (u < 0) {
            a = 2 * (-u - 1);
        } else {
            a = 2 * (u - 1) + 1;
        }

        if (v < 0) {
            b = 2 * (-v - 1);
        } else {
            b = 2 * (v - 1) + 1;
        }

//        a = rand() % (2 * n);
//        b = rand() % (2 * n);

        d[a][b] = 1;
        d[b ^ 1][a ^ 1] = 1;
    }

    forn(k, 2*n) {
        forn(i, 2*n) {
            forn(j,2*n) {
                d[i][j] |= (d[i][k] & d[k][j]);
            }
        }
    }



    int value[n];
    memset(value, 255, sizeof(value));

    forn(i, n) {
        int t = 2 * i + 1;
        int f = 2 * i;

        if (d[t][f] && d[f][t]) {
            cout << "0\n";
            return;
        }
    }

    ll mul = 1;

    forn(i, n) {
        if (value[i] != -1) {
            continue;
        }
        int t = 2 * i + 1;
        int f = 2 * i;

        if (d[t][f]) {
            forn(j, 2*n) if (d[f][j]) {
                    value[j / 2] = j % 2;
                }
        }
        if (d[f][t]) {
            forn(j, 2*n) if (d[t][j]) {
                    value[j / 2] = j % 2;
                }
        }

        if (accumulate(d[2*i], d[2*i] + 2*n, 0) == 1 && accumulate(d[2*i+1], d[2*i+1] + 2*n, 0) == 1) {
            mul = mul * 2;
            value[i] = 0;
        }
    }
    forn(i,2*n) p[i] = i;
    forn(i, 2 * n) forn(j, 2 * n) {
            if (d[i][j] && d[j][i]) {
                unite(i, j);
            }
        }

    char used[2 * n];
    clr(used);

    int id[2 * n];

    int rid[2 * n];

    int sz = 0;

    forn(i, n) {
        if (value[i] == -1) {
            int c1 = get(2 * i);
            if (!used[c1]) {
                rid[get(2 * i)] = sz;
                id[sz++] = get(2 * i);
                rid[get(2 * i + 1)] = sz;
                id[sz++] = get(2 * i + 1);
                used[get(2 * i)] = 1;
                used[get(2 * i + 1)] = 1;
            }
        }
    }
    assert(sz % 2 == 0);
    S = sz / 2;

    int O[n];
    clr(O);

    forn(i, 2 * n) forn(j, 2 * n) {
            int a = get(i);
            int b = get(j);
            if (used[a] && used[b] && d[i][j]) {
                int r1 = rid[a];
                int r2 = rid[b];
                if (r2 % 2 == 0) {
                    T0[r1] |= 1ll << r2 / 2;
                } else {
                    T1[r1] |= 1ll << r2 / 2;
                }
                O[r1 / 2] += 1;
            }
        }


    vi ids(S);
    iota(all(ids), 0);

    sort(all(ids), [&](int u, int v) {
        return O[u] > O[v];
    });



    vll TT0(sz);
    vll TT1(sz);

    forn(i, 2*S) {
        forn(j, S) {
            TT0[i] |= (((T0[ids[i / 2] * 2 + (i % 2)] >> ids[j]) & 1) << j);
            TT1[i] |= (((T1[ids[i / 2] * 2 + (i % 2)] >> ids[j]) & 1) << j);
        }
    }



    forn(i, sz) {
        T0[i] = TT0[i];
        T1[i] = TT1[i];
    }

    queue <int> q;
    clr(used);

    ll ans = mul;

    forn(i, S) {
        if (!used[i]) {
            ll mask = 0;
            used[i] = 1;
            q.push(i);

            while (!q.empty()) {
                int v = q.front();
                q.pop();

                mask |= 1ll << v;

                ll TO = T0[2 * v] | T0[2 * v + 1] | T1[2 * v] | T1[2 * v + 1];

                forn(x, S) {
                    if (TO & (1ll << x)) {
                        if (!used[x]) {
                            used[x] = 1;
                            q.push(x);
                        }
                    }
                }
            }

            ans *= rec(mask, 0ll, 0ll);
        }
    }

    cout << ans << "\n";
}


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
    int t = 1;// nxt();
#ifdef LOCAL
#else
#endif
    for (int test = 1; test <= t; ++test) {
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

template<typename T>
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

mt19937 generator;

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
