//
// Created by Evgeny Savinov on 09/01/2017.
//

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
typedef vector<vi> vvi;
typedef pair<int, int> pii;
//typedef pair<long long, long long> pii;
typedef vector<long long> vll;
typedef long double ld;
using ll = long long;
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


void pre() {

}

struct Dsu {
    vector <int *> ptrs;
    vector <int> vals;
    vector <int> p;
    vector <int> sz;
    int components;

    void init(int n) {
        p.resize(n);
        sz.resize(n);
        ptrs.reserve(n);
        vals.reserve(n);
        components = n;
        for (int i = 0; i < n; ++i) {
            p[i] = i, sz[i] = 1;
        }
    }

    void set(int *x, int y) {
        ptrs.push_back(x);
        vals.push_back(*x);
        *x = y;
    }

    void revert(int version) {
        while (ptrs.size() > version) {
            *ptrs.back() = vals.back();
            ptrs.pop_back();
            vals.pop_back();
        }
    }

    inline int get(int v) {
        if (p[v] != v) {
            return get(p[v]);
            //set(p + v, get(p[v])); //compressed path heuristic
        }
        return p[v];
    }

    inline void unite(int a, int b) {
        a = get(a);
        b = get(b);
        if (a == b) {
            return;
        }
        set(&components, components - 1);
        if (sz[a] > sz[b]) {
            swap(a, b);
        }
        set(&p[a], b);
        set(&sz[b], sz[a] + sz[b]);
    }
    inline int getVersion() {
        return vals.size();
    }
};

Dsu dsu;

enum Type {
    GET, UPDATE
};


struct query {
    int root;
    vector <int> check;
};

struct Query {
    Type type;
    query *q;
    int l, r;
    int u, v;
};

vector <Query> Q;

void processQueries(vector <int> & queries, int left, int right, vector <int> & answer) {
    if (left == right) {
        int version = dsu.getVersion();
        for (const auto & query_id : queries) {
            auto query = Q[query_id];
            if (query.type == UPDATE && query.l < left && query.r >= right) {
                dsu.unite(query.u, query.v);
            }
        }
        for (const auto & query_id : queries) {
            auto query = Q[query_id];
            if (query.type == GET && query.l == left) {
                answer[query.u] = 1;
                for (int v : query.q->check) {
                    if (dsu.get(v) == dsu.get(query.q->root)) {
                        answer[query.u] = 0;
                        break;
                    }
                }
            }
        }
        dsu.revert(version);
        return;
    }

    int version = dsu.getVersion();

    vector <int> queriesToSend;

    for (const auto & query_id : queries) {
        auto query = Q[query_id];
        if (query.type == UPDATE && query.l < left && query.r >= right) {
            dsu.unite(query.u, query.v);
        } else if ((query.type == GET && query.l >= left && query.r <= right) || (query.type == UPDATE && query.l < right && query.r >= left)) {
            queriesToSend.push_back(query_id);
        }
    }

    int mid = (left + right) / 2;

    processQueries(queriesToSend, left, mid, answer);
    processQueries(queriesToSend, mid + 1, right, answer);

    dsu.revert(version);
}


map <pii, int> M;

void genEdges(int x, int y, vector <pii> &z) {
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    int r = M[{x, y}];

    for (int k = 0; k < 4; ++k) {
        int xx = x + dx[k];
        int yy = y + dy[k];

        if (M.count({xx, yy})) {
            int id = M[{xx, yy}];
            if (r < id) {
                z.pb(mp(r, id));
            } else {
                z.pb(mp(id, r));
            }
        }
    }
}


void solve(int test) {
   int n = nxt();

   for (int i = 0; i < n; ++i) {
       pii x;
       x.x = nxt();
       x.y = nxt();
       M[x] = i;
   }

   dsu.init(n);

   map <pii, int> last;

    vector <pii> z;

   for (auto kv : M) {
       auto s = kv.x;
       genEdges(s.x, s.y, z);
   }

    sort(all(z));
    z.erase(unique(all(z)), z.end());

    for (auto e : z) {
        last[e] = 0;
    }

   int t = nxt();
   for (int i = 1; i <= t; ++i) {
       int m = nxt();
       int w = nxt();
       query *q = new query();
       auto sx = nxt();
       auto sy = nxt();
       q->root = M[{sx, sy}];
       vector <int> blocked;
       forn(_, m) {
           int x = nxt();
           int y = nxt();
           q->check.pb(M[{x, y}]);
       }
       vector <pii> blocked_e;
       forn(_, w) {
           int x = nxt();
           int y = nxt();
           genEdges(x, y, blocked_e);
       }
       sort(all(blocked_e));
       blocked_e.erase(unique(all(blocked_e)), blocked_e.end());

       for (auto e : blocked_e) {
           assert(last.count(e));
           if (last[e] <= i - 1) {
//               cerr << e.x << " " << e.y << " " << last[e] << " " << i - 1 << "\n";
               Q.push_back(Query{UPDATE, 0, last[e], i - 1, e.x, e.y});
           }
           last[e] = i;
       }
       Q.push_back(Query{GET, q, i, i, i, i});
   }

    for (auto e : z) {
//        cerr << e.x << " " << e.y << " " << last[e] << " " << t + 1 << "\n";
        Q.push_back(Query{UPDATE, 0, last[e], t + 1, e.x, e.y});
    }

    vector <int> answer(t + 1);
    vector <int> queries(Q.size());
    iota(all(queries), 0);
    processQueries(queries, 0, t + 1, answer);

   for (int i = 1; i <= t; ++i) {
        if (answer[i]) {
            cout << "ok\n";
        } else {
            cout << "fail\n";
        }
   }
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


