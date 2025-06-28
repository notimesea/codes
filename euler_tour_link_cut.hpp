#include <bits/stdc++.h>

struct euler_tour_tree {
    struct node {
        int x, s;
        node *ch[2], *p, *r;
 
        node(int y) {
            x = s = y;
            ch[0] = ch[1] = p = r = 0;
        };
 
    };
 
    int sum(node *t) {
        return t ? t->s : 0;
    }
 
    node *update(node *t) {
        if (t) {
            t->s = t->x + sum(t->ch[0]) + sum(t->ch[1]);
        }
        return t;
    }
 
    int dir(node *t) {
        return t != t->p->ch[0];
    }
 
    void connect(node *p, node *t, int d) {
        p->ch[d] = t;
        if (t) t->p = p;
        update(p);
    }
 
    node *disconnect(node *t, int d) {
        node *c = t->ch[d];
        t->ch[d] = 0;
        if (c) c->p = 0;
        update(t);
        return c;
    }
 
    bool is_root(node *t) {
        return !t->p || (t->p->ch[0] != t && t->p->ch[1] != t);
    }
 
    void rot(node *t) {
        node *p = t->p;
        int d = dir(t);
        if (!is_root(p)) {
            connect(p->p, t, dir(p));
        } else {
            t->p = p->p;
        }
        connect(p, t->ch[!d], d);
        connect(t, p, !d);
    }
 
    void splay(node *t) {
        for (; !is_root(t); rot(t)) {
            if (!is_root(t->p)) {
                rot(dir(t) == dir(t->p) ? t->p : t);
            }
        }
 
    }
 
    void join(node *s, node *t) {
        if (!s || !t) return;
        for (; s->ch[1]; s = s->ch[1]);
        splay(s);
        connect(s, t, 1);
    }
 
    node *make_node(int x, node *l = 0, node *r = 0) {
        node *t = new node(x);
        connect(t, l, 0);
        connect(t, r, 1);
        return t;
    }
 
    //  u      v           uv         vu
    // / \    / \          /\         /\
    //a   b  c   d        u  d       v  b
    //                   /          /
    //                  a          c
 
 
    //  a-u-b   c-v-d  ->  a-u-uv-d-c-v-vu-b
 
    node *link(node *u, node *v, int x = 0) {
        splay(u);
        splay(v);
 
        node * a = disconnect(u, 1);
        node * b = disconnect(v, 1);
 
        node *uv = make_node(x, u, b);
        node *vu = make_node(0, v, a);
        uv->r = vu;
        vu->r = uv;
        join(uv, vu);
        return uv;
    }
 
    void cut(node *uv) {
        splay(uv);
        join(disconnect(uv, 1), disconnect(uv, 0));
        splay(uv->r);
        disconnect(uv->r, 0);
        disconnect(uv->r, 1);
    }
 
    int sum_in_component(node *u) {
        splay(u);
        return u->s;
    }
 
    vector<int> vertices;
    vector<int> edges;
 
    vector<node *> V;
    vector<node *> E;
 
    void link(int x, int y, int ee) {
        int u = lower_bound(all(vertices), x) - vertices.begin();
        int v = lower_bound(all(vertices), y) - vertices.begin();
        assert(vertices[u] == x);
        assert(vertices[v] == y);
 
        int w = lower_bound(all(edges), ee) - edges.begin();
        assert(edges[w] == ee);
        E[w] = link(V[u], V[v]);
    }
 
    void cut(int ee) {
        int w = lower_bound(all(edges), ee) - edges.begin();
        assert(edges[w] == ee);
        cut(E[w]);
    }
 
    int get(int x) {
        int u = lower_bound(all(vertices), x) - vertices.begin();
        assert(vertices[u] == x);
        return sum_in_component(V[u]);
    }
};
 
void testTree() {
    euler_tour_tree tree;
    const int N = 3000;
    euler_tour_tree::node *nodes[N];
    euler_tour_tree::node *edges[N];
    for (int i = 0; i < N; ++i) {
        int v = rand() % 100;
        nodes[i] = tree.make_node(v);
    }
    int ss = 0;
    for (int i = 1; i < N; ++i) {
        ss += nodes[i - 1]->first;
        for (int j = 0; j < i; ++j) {
            assert(ss == tree.sum_in_component(nodes[j]));
        }
        edges[i] = tree.link(nodes[i], nodes[i >> 1]);
    }
 
    for (int i = N - 1; i > 0; --i) {
 
        tree.cut(edges[i]);
        for (int j = 0; j < i; ++j) {
            assert(ss == tree.sum_in_component(nodes[j]));
        }
        ss -= nodes[i - 1]->first;
    }
 
    exit(0);
}
