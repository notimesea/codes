#include <bits/stdc++.h>
using namespace std;

struct Hld {
    vector <int> path;
    vector <vector <int> > g;
    vector <int> position;
    vector <int> parent;
    vector <int> size;
    vector <vector <int> > onPath;
    vector <int> rootId;
    vector <int> tin;
    vector <int> tout;
    int pathCount;
    int curPosition;
    int timer;

    Hld(int n) {
        path.resize(n);
        g.resize(n);
        position.resize(n);
        parent.resize(n);
        size.resize(n);
        tin.resize(n);
        tout.resize(n);
        pathCount = 0;
        curPosition = 0;
        timer = 0;
    }

    void addEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void dfs(int v, int p) {
        tin[v] = timer++;
        size[v] = 1;

        for (int to : g[v]) {
            if (to == p) {
                continue;
            }
            dfs(to, v);
            size[v] += size[to];
        }
        tout[v] = timer++;
    }

    void build(int v, int p, int pathId) {
        onPath[pathId].push_back(v);
        path[v] = pathId;
        position[v] = curPosition++;

        int best = -1;
        for (int to : g[v]) {
            if (to == p) {
                continue;
            }
            if (best == -1 || size[best] < size[to]) {
                best = to;
            }
        }

        if (best != -1) {
            parent[best] = v;
            build(best, v, pathId);
        }

        for (int to : g[v]) {
            if (to == p || to == best) {
                continue;
            }
            onPath.push_back(vector <int>());
            rootId.push_back(to);
            parent[to] = v;
            build(to, v, pathCount++);
        }
    }

    void build() {
        dfs(0, 0);
        onPath.push_back(vector <int>());
        rootId.push_back(0);
        parent[0] = -1;
        build(0, 0, pathCount++);
    }

    bool upper(int a, int b) {
        return tin[a] <= tin[b] && tout[a] >= tout[b];
    }

    int lca(int a, int b) {
        while (!upper(rootId[path[a]], b)) {
            a = parent[rootId[path[a]]];
        }
        while (!upper(rootId[path[b]], a)) {
            b = parent[rootId[path[b]]];
        }
        if (upper(a, b)) {
            return a;
        } else {
            return b;
        }
    }

    vector <pair <int, int> > query(int a, int b = 0) {
        vector <pair <int, int> > segs;

        if (!upper(b, a)) {
            return segs;
        }

        while (path[a] != path[b]) {
            segs.push_back(make_pair(position[rootId[path[a]]], position[a]));
            a = parent[rootId[path[a]]];
        }
        segs.push_back(make_pair(position[b], position[a]));
        return segs;
    }
};
