#include <bits/stdc++.h>

mt19937 generator;

template <class K, class V>
struct node {
    K key;
    V value;
    unsigned prior;
    int cnt;

    node *l, *r;

    node(K k, V v = 0) {
        key = k;
        value = v;
        prior = generator();
        cnt = 1;
        l = r = 0;
    }

    inline friend int getCount(node * v) {
        return v ? v->cnt : 0;
    }

    inline friend V getValue(node *v) {
        return v ? v->value : 0;
    }

    inline friend void update(node * v) {
        if (v) {
            v->cnt = 1 + getCount(v->l) + getCount(v->r);
            v->value = getValue(v->l) + getValue(v->r);
        }
    }

    inline friend void split(node* v, node* &l, node* &r, int cnt) {
        if (!v) {
            return void(l = r = 0);
        }
        int k = getCount(v->l);
        if (cnt <= k) {
            split(v->l, l, v->l, cnt), r = v;
        } else {
            split(v->r, v->r, r, cnt - k - 1), l = v;
        }
        update(v);
    }

    inline friend void merge(node * &v, node *l, node *r) {
        if (!l || !r) {
            return void(v = l ? l : r);
        }
        if (l->prior > r->prior) {
            merge(l->r, l->r, r);
            v = l;
        } else {
            merge(r->l, l, r->l);
            v = r;
        }
        update(v);
    }
};

void test() {
  function <void(node*)> print = [&](node *v) {
        if (!v) return;
        print(v->l);
        printf("%d ", v->key);
        print(v->r);
    };

    int n = nxt(), m = nxt();

    node * root = 0;

    for (int i = 0; i < n; ++i) {
        merge(root, root, new node(i + 1));
    }

    while (m--) {
        int l = nxt() - 1, r = nxt();
        node *x, *y;
        split(root, x, root, r);
        split(x, y, x, l);
        merge(x, x, y);
        merge(root, x, root);
    }

    print(root);
}
