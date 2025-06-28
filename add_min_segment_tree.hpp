#include <climits>

using ll = long long;

struct Data {
    int val;
    int pos;

    Data operator + (const int &r) const {
        return Data{val + r, pos};
    }
    bool operator < (const Data &r) const {
        if (val != r.val) {
            return val < r.val;
        }
        return pos < r.pos;
    }
};

Data val[1 << 20];
ll add[1 << 20];

void build(int v, int tl, int tr) {
    if (tr - tl == 1) {
        val[v] = Data{0, tl};
        add[v] = 0;
        return;
    }
    int tm = (tl + tr) / 2;
    build(v + v, tl, tm);
    build(v + v + 1, tm, tr);
    add[v] = 0;
    val[v] = min(val[v + v], val[v + v + 1]);
}

void push(int v) {
    add[v + v] += add[v];
    add[v + v + 1] += add[v];
    add[v] = 0;
}

void update(int v, int tl, int tr, int l, int r, int x) {
    if (l >= r) return;
    if (tl == l && tr == r) {
        add[v] += x;
        return;
    }
    push(v);
    int tm = (tl + tr) / 2;

    update(v + v, tl, tm, l, min(r, tm), x);
    update(v + v + 1, tm, tr, max(tm, l), r, x);

    val[v] = min(val[v + v] + add[v + v], val[v + v + 1] + add[v + v + 1]);
}

Data get(int v, int tl, int tr, int l, int r) {
    if (l >= r) return Data{INT_MAX, -1};
    if (l == tl && r == tr) {
        return val[v] + add[v];
    }
    push(v);
    int tm = (tl + tr) / 2;
    Data res = min(get(v + v, tl, tm, l, min(r, tm)), get(v + v + 1, tm, tr, max(l, tm), r));
    val[v] = min(val[v + v] + add[v + v], val[v + v + 1] + add[v + v + 1]);
    return res;
}
