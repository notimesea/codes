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


//maximal number of vertices
const int N = 1111;

struct minCostFlow {
    struct edge {
        int from, to;
        long long cap, flow, cost;
    };


    vector <edge> edges;
    vector<int> g[N];
    int vsize;

    int p[N];
    char used[N];
    long long dist[N];
    long long pi[N];


    void addEdge(int from, int to, long long cap, long long cost) {
        g[from].pb(edges.size());
        edges.push_back(edge{from, to, cap, 0, cost});
        g[to].pb(edges.size());
        edges.pb(edge{to, from, 0, 0, -cost});
    }


    bool fb(int s, int t) {
        memset(p, 0xff, vsize * sizeof(int));
        memset(dist, 0x3f, vsize * sizeof(long long));
        memset(used, 0, vsize * sizeof(char));
        dist[s] = 0;

        priority_queue<pair <long long, int> > q;
        q.push(mp(0, s));
        while (!q.empty()) {
            auto z = q.top();
            q.pop();
            if (dist[z.y] != -z.x) continue;
            int v = z.y;
            for (int ed : g[v]) {
                edge &e = edges[ed];
                int to = e.to;
                long long len = e.cost;
                if (e.cap > e.flow && dist[to] > dist[v] + len + pi[to] - pi[v]) {
                    dist[to] = dist[v] + len + pi[to] - pi[v];
                    p[to] = ed;
                    q.push(mp(-dist[to
                    ], to));
                }
            }
        }

        assert(p[t] != -1);
        return p[t] != -1;
    }

    long long cost;
    long long flow;

    long long pushFlow(int s, int t, long long need) {
        long long addFlow = need;
        for (int cur = t, e = p[cur]; cur != s; cur = edges[e].from, e = p[cur]) {
            addFlow = min(addFlow, edges[e].cap - edges[e].flow);
        }
        cost += (dist[t] - pi[t]) * addFlow;
        flow += addFlow;
        for (int cur = t, e = p[cur]; cur != s; cur = edges[e].from, e = p[cur]) {
            edges[e].flow += addFlow;
            edges[e ^ 1].flow -= addFlow;
        }
        for (int i = 0; i < vsize; ++i) {
            pi[i] -= dist[i];
            assert(pi[i] >= LLONG_MIN / 2);
        }
//        ll m = *min_element(pi, pi + vsize);
//        for (int i = 0; i < vsize; ++i) {
//            pi[i] -= m;
//        }
        return addFlow;
    }

    long long inf = 0x3f3f3f3f3f3f3f3fll;
    bool check() {
        memset(p, 0xff, vsize * sizeof(int));
        memset(pi, 0, vsize * sizeof(long long));
        int x = -1;

        for (int i = 0; i < vsize; ++i) {
            x = -1;
            for (int j = 0; j < (int)edges.size(); ++j) {
                const edge & e = edges[j];
                if (e.flow < e.cap && pi[e.from] + e.cost < pi[e.to]) {
                    pi[e.to] = max(-inf, pi[e.from] + e.cost);
                    p[e.to] = j;
                    x = e.to;
                }
            }
        }
        return x == -1;
    }

    void calcMinCostFlow(int s, int t, long long needFlow) {
        while (needFlow && fb(s, t)) {
            needFlow -= pushFlow(s, t, needFlow);
        }
    }

    minCostFlow(int vertices) {
        flow = 0;
        vsize = vertices;
        cost = 0;
        memset(pi, 0, vsize * sizeof(long long));
    }
};

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

    int t = 1;

    while (t--) {
        int n = nxt();
        int k = nxt();
        int m1 = nxt();
        int m2 = nxt();

        vector <int> a(n);

        for (int i = 0; i < n; ++i) {
            a[i] = nxt();
        }

        vector <int> b(n);

        for (int i = 0; i < n; ++i) {
            b[i] = nxt();
        }


        long long s = 0;

        ll o[n + 1];
        clr(o);

        minCostFlow g(n + 1 + 2);

        int s1 = n + 1;
        int t1 = n + 2;

        for (int i = 0; i + k <= n; ++i) {
            g.addEdge(i + k, i, g.inf, k - m2);
            g.addEdge(i, i + k, g.inf, -m1);
        }

        for (int i = 0; i < n; ++i) {
            g.addEdge(i + 1, i, g.inf, 1);
            g.addEdge(i, i + 1, g.inf, 0);
        }

        for (int i = 0; i < n; ++i) {
            s += b[i];
            ll c = a[i] - b[i];
            o[i + 1] += c;
            o[i] -= c;
        }

        long long needFlow = 0;

        for (int i = 0; i <= n; ++i) {
            //o[i] = -o[i];
            if (o[i] > 0) {
                g.addEdge(s1, i, o[i], 0);
                needFlow += o[i];
            } else {
                g.addEdge(i, t1, -o[i], 0);
            }
        }

        assert(g.check());
        if (true) {
            g.calcMinCostFlow(s1, t1, needFlow);
            assert(g.flow == needFlow);
            //cout << g.cost + s << "\n";

            long long p = LLONG_MAX;

            long long ans[n + 1];

            for (int i = 0; i < n + 1; ++i) {
                p = min(p, g.pi[i]);
            }

            for (int i = 0; i < n + 1; ++i) {
                ans[i] = g.pi[i] - p;
            }

            for (int i = 0; i < n; ++i) {
                ans[i] = ans[i + 1] - ans[i];
            }

            ll ANS = 0;
            for(int i = 0; i < n; ++i) {
                ANS += ans[i] ? a[i] : b[i];
            }
            cout << ANS << "\n";

            for (int i = 0; i < n; ++i) {
                cout << (ans[i] ? "S" : "E");
            }
            cout << "\n";
        }
    }


#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
}
