#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define all(x) (x).begin(), (x).end()

namespace DOM {
    const int N=1e6+5,M=1e6+5;
    int cnt,dfn_cnt,last[N],lastpre[N],lastsdom[N],dfn[N],id[N],par[N],fa[N],best[N],sdom[N],idom[N],size[N];
    struct edge{int y,last;}E[M*2+N];
    int find(int x)
    {
        if (x==fa[x]) return x;
        int y=find(fa[x]);
        if (dfn[sdom[best[fa[x]]]]<dfn[sdom[best[x]]]) best[x]=best[fa[x]];
        return fa[x]=y;
    }
    void link(int *last,int x,int y) {E[cnt]=(edge){y,last[x]},last[x]=cnt++;}
    void dfs(int p)
    {
        dfn[p]=dfn_cnt,id[dfn_cnt]=p,++dfn_cnt;
        for (int i=last[p],nxt;~i;i=E[i].last) if (!~dfn[nxt=E[i].y]) par[nxt]=p,dfs(nxt);
    }
    void calc(int n)
    {
        for (int i=0,num;i<n;++i) num=id[i],fa[num]=num,best[num]=num,sdom[num]=num;
        for (int i=n-1,p;i;--i)
        {
            p=id[i];
            for (int j=lastpre[p],nxt;~j;j=E[j].last) if (~dfn[nxt=E[j].y])
                {
                    find(nxt);
                    if (dfn[sdom[best[nxt]]]<dfn[sdom[p]]) sdom[p]=sdom[best[nxt]];
                }
            link(lastsdom,sdom[p],p),fa[p]=par[p];
            p=id[i-1];
            for (int j=lastsdom[p],nxt;~j;j=E[j].last)
            {
                find(nxt=E[j].y);
                if (sdom[best[nxt]]==p) idom[nxt]=p; else idom[nxt]=best[nxt];
            }
        }
        for (int i=1,p;i<n;++i)
        {
            p=id[i];
            if (idom[p]!=sdom[p]) idom[p]=idom[idom[p]];
        }
    }
}

void solve(int test) {
    int n = nxt();

    int m = nxt();

    int s = nxt() - 1;


    vll dist(n, LLONG_MAX);

    vector <pair <int, int> > g[n];

    forn(i, m) {
        int u = nxt() - 1;
        int v = nxt() - 1;
        int w = nxt();

        g[u].pb({v, w});
        g[v].pb({u, w});
    }


    auto cmp = [&](int u, int v) {
        if (dist[u] != dist[v]) {
            return dist[u] < dist[v];
        }
        return u < v;
    };

    set <int, decltype(cmp)> q(cmp);

    dist[s] = 0;
    q.insert(s);

    int cnt = 0;

    vi used(n);

    while (!q.empty()) {
        int v = *q.begin();
        q.erase(q.begin());
        used[v] = 1;
        ++cnt;

        for (auto e : g[v]) {
            int to = e.x;
            ll nlen = dist[v] + e.y;

            if (nlen < dist[to]) {
                q.erase(to);
                dist[to] = nlen;
                q.insert(to);
            }
        }
    }

    memset(DOM::dfn,-1,sizeof(int)*n);
    memset(DOM::last,-1,sizeof(int)*n);
    memset(DOM::lastpre,-1,sizeof(int)*n);
    memset(DOM::lastsdom,-1,sizeof(int)*n);


    for (int i = 0; i < n; ++i) {
        if (!used[i]) continue;
        for (auto to : g[i]) {
            if (!used[to.x]) continue;
            if (dist[to.x] == dist[i] + to.y) {
                int x = i;
                int y = to.x;
                DOM::link(DOM::last,x,y);
                DOM::link(DOM::lastpre,y,x);
            }
        }
    }
    DOM::dfs(s);
    DOM::calc(DOM::dfn_cnt);

    int ans = 0;

    for (int i=DOM::dfn_cnt-1,p;i;--i)
    {
        p=DOM::id[i],++DOM::size[p];
        ans = max(ans, DOM::size[p]);
        DOM::size[DOM::idom[p]]+=DOM::size[p];
    }

    cout << ans << "\n";
}
