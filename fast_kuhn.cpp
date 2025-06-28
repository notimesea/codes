#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

template<typename T>
void input(T &x) {
    cin >> x;
}

template<typename T = long long>
T nxt() {
    T x;
    input(x);
    return x;
}

const int V = 3000;
const int E = 1500 * 1500;

int e = 1, he[V], ne[E], to[E];
int cc = 1, u[V], pa[V];

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void add( int a, int b ) {
    ne[e] = he[a], to[e] = b, he[a] = e++;
}

int dfs(int v) {
    u[v] = cc;
    for (int x, e = he[v]; e; e = ne[e])
        if (pa[x = to[e]] == -1 || (u[pa[x]] != cc && dfs(pa[x]))) {
            pa[x] = v, pa[v] = x;
            return 1;
        }
    return 0;
}

char used[V][V];

int main() {
    //#define int long
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
#define fname "a"
    //freopen(fname".in", "r", stdin);
    //freopen(fname".out", "w", stdout);
#endif

    int n = nxt();

    int a[n];

    for (int i = 0; i < n; ++i) {
        a[i] = nxt() - 1;
    }

    int m = nxt();

    for (int i = 0; i < m; ++i) {
        int u = nxt() - 1;
        int v = nxt() - 1;
        used[u][v] = used[v][u] = 1;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i] == 0 && a[j] == 1 && !used[i][j]) {
                add(i, j);
                //cerr << i << " " << j << endl;
            }
        }
    }

    fill(pa, pa + V, -1);
    int M = 0;
    forn(i, n) {
        if (pa[i] == -1) {
            for (int x, e = he[i]; e; e = ne[e])
                if (pa[x = to[e]] == -1) {
                    pa[i] = x, pa[x] = i;
                    M++;
                    break;
                }
        }
    }

    for (int run = 1; run;) {
        run = 0, cc++;
        forn(i, n) {
            if (pa[i] == -1 && dfs(i))
                M++, run = 1;
        }
    }

    cout << n - M << "\n";


#ifdef LOCAL
    cout << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
}
