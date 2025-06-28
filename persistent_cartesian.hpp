#include <climits>

using ll = long long;

struct hdata {
    ll h1;
    ll h2;
    ll h3;

    hdata() {
        h1 = 0;
        h2 = 0;
        h3 = 1;
    }

    hdata operator+(const hdata &r) const {
        hdata res;
        res.h1 = h1 * r.h3 + r.h1;
        res.h2 = r.h2 * h3 + h2;
        res.h3 = h3 * r.h3;
        return res;
    }

    hdata(int key) {
        h1 = key;
        h2 = key;
        h2 = Q;
    }
};

struct item;

typedef shared_ptr<item> pitem;

hdata geth(pitem t);

int getq(pitem t);

struct item {
    int q;
    int value;
    hdata hash;
    pitem l, r;
    char rev;

    item() {}

    item(int value, pitem l = nullptr, pitem r = nullptr) : value(value), l(l), r(r) {
        q = 1 + getq(l) + getq(r);
        hash = geth(l) + value + geth(r);
        rev = 0;
    }
    item(pitem x) : q(x->q), value(x->value), hash(x->hash), l(x->l), r(x->r), rev(1) {
        swap(hash.h1, hash.h2);
    }
};

hdata empty;

hdata geth(pitem t) {
    if (t != nullptr) return t->hash;
    else return empty;
}

int getq(pitem t) {
    if (t != nullptr) return t->q;
    else return 0;
}

pitem rev(pitem v) {
    if (v == nullptr) return nullptr;
    return make_shared<item>(v);
}

pitem push(pitem v) {
    if (v == nullptr) return nullptr;
    if (!v->rev) return v;
    return make_shared<item>(v->value, rev(v->r), rev(v->l));
}

mt19937 gen;

bool random(int a, int b) {
    return gen() % (a + b) < a;
}

inline pitem merge(pitem l, pitem r) {
    if (l == nullptr || r == nullptr)
        return l != nullptr ? l : r;
    else if (random(l->q, r->q)) {
        l = push(l);
        return make_shared<item>(l->value, l->l, merge(l->r, r));
    } else {
        r = push(r);
        return make_shared<item>(r->value, merge(l, r->l), r->r);
    }
}

inline pair<pitem, pitem> split(pitem root, int cnt) {
    if (root == nullptr)
        return make_pair(nullptr, nullptr);
    root = push(root);
    if (cnt <= getq(root->l)) {
        pair<pitem, pitem> splitted = split(root->l, cnt);
        return make_pair(splitted.first, make_shared<item>(root->value, splitted.second, root->r));
    } else {
        pair<pitem, pitem> splitted = split(root->r, cnt - getq(root->l) - 1);
        return make_pair(make_shared<item>(root->value, root->l, splitted.first), splitted.second);
    }
}

void print(pitem p, int d = 0) {
    if (p == nullptr) {
        return;
    }
    p = push(p);
    print(p->l, d + 1);
    cout << p->value << " ";
    print(p->r, d + 1);
}

pitem reverse(pitem root, int l, int r) {
    auto t1 = split(root, l);
    auto t2 = split(t1.y, r - l);
    t2.x = rev(t2.x);
    return merge(t1.x, merge(t2.x, t2.y));
}
