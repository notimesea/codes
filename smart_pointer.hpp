#include <bits/stdc++.h>

template <class item>
struct pitem {
    item *data;
    int *counter;

    pitem() {
        data = 0;
        counter = new int(1);
    }

    pitem(const pitem &r) : data(r.data), counter(r.counter) {
        ++*counter;
    }

    void release() {
        if (!--*counter) {
            delete data;
            delete counter;
        }
    }

    pitem &operator=(const pitem &r) {
        if (this == &r) return *this;
        release();
        data = r.data;
        counter = r.counter;
        ++*counter;
        return *this;
    }
    pitem (item *i) {
        data = i;
        counter = new int(1);
    }

    bool operator==(const pitem &r) const {
        return data == r.data;
    }

    bool operator!=(const pitem &r) const {
        return !(operator==(r));
    }

    ~pitem() {
        release();
    }

    const item *operator->() const {
        return data;
    }
};
