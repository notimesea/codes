#include <bits/stdc++.h>
using namespace std;

struct Hld {
    vector<int> path;
    vector<vector<int> > g;
    vector<int> position;
    vector<int> parent;
    vector<int> size;
    vector<vector<int> > onPath;
    vector<int> root;
    vector<int> tin;
    vector<int> tout;
    int pathCount;
    int curPosition;
    int timer;

    Hld(int n = 0) {
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
    
    vector <pair <int, int> > st;
    
    void build(int v, int p) {
        st.push_back(mp(v, p));
        while (!st.empty()) {
            v = st.back().x, p = st.back().y;
            st.pop_back();
            onPath[path[v]].push_back(v);
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
            
            for (int to : g[v]) {
                if (to == p || to == best) {
                    continue;
                }
                onPath.push_back(vector<int>());
                root.push_back(to);
                parent[to] = v;
                path[to] = pathCount++;
            }

            for (int to : g[v]) {
                if (to == p || to == best) {
                    continue;
                }
                st.push_back(mp(to, v));
            }

            if (best != -1) {
                parent[best] = v;
                path[best] = path[v];
                st.push_back(mp(best, v));
            }
        }
    }

    void build() {
        dfs(0, 0);
        onPath.push_back(vector<int>());
        root.push_back(0);
        parent[0] = -1;
        path[0] = pathCount++;
        build(0, 0);
    }

    bool upper(int a, int b) {
        return tin[a] <= tin[b] && tout[a] >= tout[b];
    }

    int lca(int a, int b) {
        while (!upper(root[path[a]], b)) {
            a = parent[root[path[a]]];
        }
        while (!upper(root[path[b]], a)) {
            b = parent[root[path[b]]];
        }
        if (upper(a, b)) {
            return a;
        } else {
            return b;
        }
    }

    vector<pair<int, int> > query(int a, int b = 0) {
        vector<pair<int, int> > segs;

        if (!upper(b, a)) {
            return segs;
        }

        while (path[a] != path[b]) {
            segs.push_back(make_pair(position[root[path[a]]], position[a]));
            a = parent[root[path[a]]];
        }
        segs.push_back(make_pair(position[b], position[a]));
        return segs;
    }
};
