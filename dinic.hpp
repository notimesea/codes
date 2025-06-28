// Dinic max flow implementation.
#include <bits/stdc++.h>

struct Dinic {

#define i64 long long
    static const int INF = 0x7fffffff;
    static const int MAXN = 1 << 20, MAXE = 1 << 22;

    int src, snk, nNode, nEdge;

    int Q[MAXN], fin[MAXN], pro[MAXN], dist[MAXN];
    int flow[MAXE], cap[MAXE], next[MAXE], to[MAXE];


    inline void init(int _src, int _snk, int _n) {
        src = _src, snk = _snk, nNode = _n, nEdge = 0;
        assert(nNode < MAXN);
        memset(fin, -1, nNode * sizeof(fin[0]));
    }

    inline void add(int u, int v, int c) {
        assert(u < nNode);
        assert(v < nNode);
        assert(nEdge < MAXE);
        to[nEdge] = v, cap[nEdge] = c, flow[nEdge] = 0, next[nEdge] = fin[u], fin[u] = nEdge++;
        assert(nEdge < MAXE);
        to[nEdge] = u, cap[nEdge] = 0, flow[nEdge] = 0, next[nEdge] = fin[v], fin[v] = nEdge++;
    }

    bool bfs() {
        int st, en, i, u, v;
        memset(dist, -1, nNode * sizeof(dist[0]));

        dist[src] = st = en = 0;
        Q[en++] = src;
        while (st < en) {
            u = Q[st++];
            for (i = fin[u]; ~i; i = next[i]) {
                v = to[i];
                if (flow[i] < cap[i] && dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    Q[en++] = v;
                }
            }
        }
        return dist[snk] != -1;
    }

    int dfs(int u, int fl) {
        if (u == snk) return fl;
        for (int &e = pro[u], v, df; ~e; e = next[e]) {
            v = to[e];
            if (flow[e] < cap[e] && dist[v] == dist[u] + 1) {
                df = dfs(v, min(cap[e] - flow[e], fl));
                if (df > 0) {
                    flow[e] += df;
                    flow[e ^ 1] -= df;
                    return df;
                }
            }
        }
        return 0;
    }

    int dinitz() {
        int ret = 0;
        int df;
        while (bfs()) {
            memcpy(pro, fin, nNode * sizeof(fin[0]));
            while (true) {
                df = dfs(src, INF);
                if (df) ret += df;
                else break;
            }
        }
        return ret;
    }

#undef CLR
#undef SET
#undef i64
} d;
