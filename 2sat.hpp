#include <bits/stdc++.h>
using namespace std;

// 2-SAT solver based on Kosaraju's SCC algorithm
// Variables are indexed from 0..n-1. For each variable x we use
// indices 2*x for x and 2*x+1 for !x.
struct sat2 {
    int n;

    vector <vector <int> > g;
    vector <vector <int> > gr;
    vector <int> order;
    vector <int> comp;
    vector <int> used;

    sat2(int nn) {
        n = nn;
    }

    sat2(){

    }

    // allocate internal structures for n variables
    inline void init() {
        g.assign(n + n, vector <int>());
        gr.assign(n + n, vector <int>());
        used.assign(n + n, 0);
        comp.assign(n + n, -1);
    }

    // add implication u -> v
    inline void add(int u, int v) {
        g[u].push_back(v);
        gr[v].push_back(u);
    }

    // first pass of Kosaraju's algorithm
    inline void dfs1(int v) {

        used[v] = 1;
        for (int to : g[v]) {
            if (!used[to]) {
                dfs1(to);
            }
        }
        order.push_back(v);
    }

    // second pass assigning component numbers
    inline void dfs2(int v, int c) {

        comp[v] = c;
        for (int to : gr[v]) {
            if (comp[to] == -1) {
                dfs2(to, c);
            }
        }
    }

    // returns true if the 2-SAT instance is satisfiable
    inline bool check() {

        for (int i = 0; i < 2 * n; ++i) {
            if (!used[i]) {
                dfs1(i);
            }
        }

        reverse(order.begin(), order.end());

        int c = 0;

        for (int x : order) {
            if (comp[x] == -1) {
                dfs2(x, c++);
            }
        }

        for (int i = 0; i < n; ++i) {
            if (comp[i + i] == comp[i + i + 1]) {
                return false;
            }
        }
        return true;
    }
};
