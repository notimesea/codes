#include <climits>

using ll = long long;

struct Line {
    ll m, b;

    ll eval(ll x) {
        return m * x + b;
    }

    bool operator==(const Line &r) const {
        return m == r.m && b == r.b;
    }

    bool operator<(const Line &r) const {
        return m < r.m || (m == r.m && b < r.b);
    }
};


ll comp(Line a, Line b, Line c) {
    return (b.m - a.m) * (c.b - a.b) + (b.b - a.b) * (a.m - c.m);
}

struct item;
typedef item * pitem;

struct item {
    Line line;

    item *right_most;
    item *left_most;

    long prior;
    item * l, * r;
    item (Line line) : line(line), prior(rand()), l(nullptr), r(nullptr), right_most(this), left_most(this) { }

    void upd() {
        left_most = right_most = this;
        if (r) right_most = r->right_most;
        if (l) left_most = l->left_most;
    }
};


pitem prev(pitem t) {
    if (!t->l) return nullptr;
    return t->l->right_most;
}

pitem next(pitem t) {
    if (!t->r) return nullptr;
    return t->r->left_most;
}

bool shouldSplitLeft(pitem t, pitem par, Line v) {
    auto pr = prev(t) ? prev(t) : par;
    if (pr == nullptr) {
        return false;
    }

    Line p = pr->line;
    Line cur = t->line;

    return comp(p, cur, v) <= 0;
}

bool shouldSplitRight(pitem t, pitem par, Line v) {
    auto nx = next(t) ? next(t) : par;
    if (nx == nullptr) {
        return false;
    }

    Line n = nx->line;
    Line cur = t->line;

    return comp(v, cur, n) <= 0;
}

void split(pitem t, Line key, pitem &l, pitem &r) {
    if (!t) {
        l = r = nullptr;
        return;
    }

    if (t->line < key) {
        split(t->r, key, t->r, r), l = t;
    } else {
        split(t->l, key, l, t->l),  r = t;
    }
    t->upd();
}

void splitLeft(pitem t, pitem par, Line v, pitem &l, pitem &r) {
    if (!t) {
        l = r = nullptr;
        return;
    }

    if (shouldSplitLeft(t, par, v))
        splitLeft(t->l, par, v, l, t->l),  r = t;
    else
        splitLeft(t->r, t, v, t->r, r),  l = t;
    t->upd();
}

void splitRight(pitem t, pitem par, Line v, pitem &l, pitem &r) {
    if (!t) {
        l = r = nullptr;
        return;
    }

    if (shouldSplitRight(t, par, v))
        splitRight(t->r, par, v, t->r, r),  l = t;
    else
        splitRight(t->l, t, v, l, t->l),  r = t;

    t->upd();
}

void splitLmost(pitem t, pitem & l, pitem & r) {
    assert(t);
    if (t->l) {
        splitLmost(t->l, l, t->l), r = t;
    } else {
        l = t;
        r = t->r;
        t->r = nullptr;
    }
    t->upd();
}

void merge (pitem & t, pitem l, pitem r) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge (l->r, l->r, r),  t = l;
    else
        merge (r->l, l, r->l),  t = r;

    if (t) t->upd();
}

struct State {
    int t;
    Line line;

    pitem cutL;
    pitem cutR;
};

struct Hull {
    pitem cur;
    vector <State> h;

    void rollback(int t) {
        while (!h.empty() && h.back().t >= t) {
            auto s = h.back();

            pitem l, r, _;
            split(cur, s.line, l, r);
            splitLmost(r, _, r);

            assert(_->line == s.line);

            merge(l, l, s.cutL);
            merge(r, s.cutR, r);
            merge(cur, l, r);

            h.pop_back();
        }
    }

    void add(int t, const Line &line) {
        pitem l, r;
        split(cur, line, l, r);

        if (l != nullptr) {
            auto last = l->right_most;
            if (last->line.m == line.m && last->line.b <= line.b) return merge(cur, l, r);

        }

        State n{};
        n.t = t;
        n.line = line;
        splitLeft(l, nullptr, line, l, n.cutL);
        splitRight(r, nullptr, line, n.cutR, r);

        merge(cur, l, new item(line));
        merge(cur, cur, r);

        h.push_back(n);
    }

    ll eval(ll x) {
        if (cur == nullptr) {
            return LLONG_MAX / 2;
        }
        ll res = LLONG_MAX / 2;
        auto p = cur;
        while (p) {
            res = min(res, p->line.eval(x));

            auto pr = prev(p);

            if (pr && pr->line.eval(x) < p->line.eval(x)) {
                p = p->l;
            } else {
                p = p->r;
            }
        }

        return res;
    }
};
