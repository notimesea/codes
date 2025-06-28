#include "bits/stdc++.h"

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

template<typename T = int>
inline T nxt() {
    T res;
    input(res);
    return res;
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

struct edge {
    int u, v;
    int len;
    int id;

    bool operator<(const edge & e) const {
        return len < e.len;
    }
};

vector <edge> edges;

Dsu dsu;

enum Type {
    GET, UPDATE
};

struct Query {
    Type type;
    int l, r;
    int u, v;
};

void processQueries(vector <Query> & queries, int left, int right, vector <int> & answer) {
    if (left == right) {
        int version = dsu.getVersion();
        for (const auto & query : queries) {
            if (query.type == UPDATE && query.l < left && query.r >= right) {
                dsu.unite(query.u, query.v);
            }
        }
        for (const auto & query : queries) {
            if (query.type == GET && query.l == left) {
                answer[query.u] = (dsu.components == 1);
            }
        }
        dsu.revert(version);
        return;
    }

    int version = dsu.getVersion();

    vector <Query> queriesToSend;

    for (const auto & query : queries) {
        if (query.type == UPDATE && query.l < left && query.r >= right) {
            dsu.unite(query.u, query.v);
        } else if ((query.type == GET && query.l >= left && query.r <= right) || (query.type == UPDATE && query.l < right && query.r >= left)) {
            queriesToSend.push_back(query);
        }
    }

    int mid = (left + right) / 2;

    processQueries(queriesToSend, left, mid, answer);
    processQueries(queriesToSend, mid + 1, right, answer);

    dsu.revert(version);
}

int main() {
    //#define int long
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
#define fname "onearmedbandit"
    //freopen(fname".in", "r", stdin);
    //freopen(fname".out", "w", stdout);
#endif

    int n = nxt(), m = nxt();

    edges.resize(m);

    for (int i = 0; i < m; ++i) {
        edges[i].u = nxt() - 1;
        edges[i].v = nxt() - 1;
        edges[i].len = nxt();
        edges[i].id = i;
    }

    sort(edges.begin(), edges.end());

    int l = 0, r = edges.back().len - edges.front().len;

    dsu.init(n);

    while (l < r) {
        int mid = (l + r) / 2;

        int j = 0;

        vector <Query> queries;

        for (int i = 0; i < m; ++i) {
            while (j < m && edges[j].len <= edges[i].len + mid) {
                ++j;
            }
            queries.push_back({UPDATE, 2 * i, 2 * j, edges[i].u, edges[i].v});
            if (j - i >= n - 1) queries.push_back({GET, 2 * j - 1, 2 * j - 1, i, i});
        }

//        for (auto q : queries) {
//            if (q.type == GET) {
//                cout << "GET " << q.l << " " << q.r << " " << q.u << endl;
//            } else {
//                cout << "UPDATE " << q.l << " " << q.r << " " << q.u << " " << q.v << endl;
//            }
//        }

        vector <int> answer(m);

        processQueries(queries, 0, 2 * m - 1, answer);


        int ok = 0;

        for (int i = 0; i < m; ++i) {
            ok += answer[i];
            //cout << answer[i] << " ";
        }
        //cout << "\n";
        if (ok) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    vector <Query> queries;

    int j = 0;

    for (int i = 0; i < m; ++i) {
        while (j < m && edges[j].len <= edges[i].len + l) {
            ++j;
        }
        queries.push_back({UPDATE, 2 * i, 2 * j, edges[i].u, edges[i].v});
        queries.push_back({GET, 2 * j - 1, 2 * j - 1, i, i});
    }


    vector <int> answer(m);

    processQueries(queries, 0, 2 * m - 1, answer);

    int pos = -1;

    for (int i = 0; i < m; ++i) {
        if (answer[i]) {
            pos = i;
            break;
        }
    }

    for (int i = pos; i < m && edges[i].len <= edges[pos].len + l; ++i) {
        int x = dsu.get(edges[i].u);
        int y = dsu.get(edges[i].v);
        if (x != y) {
            cout << edges[i].id + 1 << " ";
            dsu.unite(x, y);
        }
    }


#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
}
