#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < (n); ++i)
#define ford(i, n) for (int i = (n) - 1; i >= 0; --i)
#define pii pair <int, int>
#define vi vector <int>
#define fi first
#define se second

const int N = 1010;
vector<pair<pii, string>> allEdges;
vector<int> globAns;

vector<int> g[N], gt[N];
int used[N];
struct TEdge
{
	int from, to, w;
	int num;
	TEdge() {}
	TEdge(int from, int to, int w, int num): from(from), to(to), w(w), num(num) {}
};

void dfs(int v)
{
    for (int to: g[v])
        if (used[to] == -1) {
            used[to] = v;
            dfs(to);
        }
}

bool check(int root, int n, const vector<pii>& edges)
{
    forn (i, n) g[i].clear();
    for (auto ed: edges)
        g[ed.fi].pb(ed.se);
    forn (i, n) used[i] = -1;
    used[root] = root;
    dfs(root);
    forn (i, n) if (used[i] == -1) return false;
    return true;
}

void dfs1(int v, vi& order)
{
    used[v] = true;
    for (int to: g[v])
        if (!used[to])
            dfs1(to, order);
    order.pb(v);
}

void dfs2(int v, int color, vi& newcomp)
{
    used[v] = true;
    newcomp[v] = color;
    for (int to: gt[v])
        if (!used[to])
            dfs2(to, color, newcomp);
}

int condensation(int n, const vector<pii>& zeroEdges, vi& res)
{
    forn (i, n) { g[i].clear(); gt[i].clear(); }
    for (auto ed: zeroEdges) {
        g[ed.fi].pb(ed.se);
        gt[ed.se].pb(ed.fi);
    }
    int q = 0;
    forn (i, n) used[i] = false;
    vi order;
    forn (i, n)
        if (!used[i])
            dfs1(i, order);
    forn (i, n) used[i] = false;
    
    ford (i, n){
        int v = order[i];
        if (!used[v])
        {
            dfs2(v, q, res);
            ++q;
        }
    }
    return q;
}

void dfs_zero(int v, const vi& comp)
{
    for (int to: g[v])
        if (comp[to] == comp[v] && used[to] == -1)
        {
            used[to] = v;
            dfs_zero(to, comp);
        }
}

int findMST(vector<TEdge> edges, int n, int root)
{
    const int INF = 1e9;
    int res = 0;
    vi minEdge(n, INF);
    minEdge[root] = 0;
    for (auto ed : edges)
    {
        minEdge[ed.to] = min(minEdge[ed.to], ed.w);
    }
    forn (i, n)
        res += minEdge[i];
    vector<pii> zeroEdges;
    for (TEdge& ed: edges)
    {
        ed.w -= minEdge[ed.to];
        if (ed.w == 0)
            zeroEdges.pb(mp(ed.from, ed.to));
    }
    if (check(root, n, zeroEdges))
    {
        for (auto ed: edges)
        if (ed.w == 0)
        {
            if (used[ed.to] == ed.from) {
                globAns.pb(ed.num);
                used[ed.to] = -1;
            }
        }
        return res;
    }
    vi newComponents(n);
    vector<TEdge> newEdges;
    int newN = condensation(n, zeroEdges, newComponents);
    for (auto ed: edges) {
        int u = ed.from, v = ed.to;
        u = newComponents[u], v = newComponents[v];
        if (u != v) 
            newEdges.pb(TEdge(u, v, ed.w, ed.num));
    }
    res += findMST(newEdges, newN, newComponents[root]); 
    
    forn (i, n) g[i].clear();
    for (pii w : zeroEdges) g[w.fi].pb(w.se);
    forn (i, n) used[i] = -1;
    dfs_zero(root, newComponents);
    for (auto ed: edges)
        if (find(all(globAns), ed.num) != globAns.end())
        {
            assert(used[ed.to] == -1);
            used[ed.to] = ed.to;
            dfs_zero(ed.to, newComponents);
        }
    for (auto ed: edges)
    if (ed.w == 0)
    {
        if (used[ed.to] == ed.from)
        {
    //        cerr << "0 " << ed.num << endl;
            globAns.pb(ed.num);
            used[ed.to] = -1;
        }
    }
    return res;
}   
