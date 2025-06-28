#include <bits/stdc++.h>

template<long long modulo>
struct Number {
    long long value;

    Number(const long long &v = 0) : value(((v % modulo) + modulo) % modulo) { }

    Number<modulo> operator+(const Number<modulo> &r) const {
        return Number<modulo>{(value + r.value) % modulo};
    }

    Number<modulo>& operator+=(const Number<modulo> &r) {
        return *this = operator+(r);
    }

    Number<modulo> operator-(const Number<modulo> &r) const {
        return Number<modulo>{(value - r.value + modulo) % modulo};
    }

    Number<modulo>& operator-=(const Number<modulo> &r) {
        return *this = operator-(r);
    }

    Number<modulo> operator*(const Number<modulo> &r) const {
        return Number<modulo>{(value * r.value) % modulo};
    }

    Number<modulo>& operator*=(const Number<modulo> &r) {
        return *this = operator*(r);
    }

    Number<modulo> reciprocal() const {
        long long x = value;
        long long res = 1;
        while (x != 1) {
            res = (res * (-modulo / x + modulo)) % modulo;
            x = modulo % x;
        }
        assert(res * value % modulo == 1);
        return res;
    }

    Number<modulo> pow(long long n) const {
        Number<modulo> res = 1;
        Number<modulo> a = *this;

        while (n) {
            if (n & 1) {
                res = res * a;
            }
            a = a * a;
            n >>= 1;
        }

        return res;
    }

    Number<modulo> operator/(const Number<modulo> &r) const {
        return operator*(r.reciprocal());
    }

    Number<modulo>& operator/=(const Number<modulo> &r) {
        return *this = operator/(r.reciprocal());
    }

    bool operator==(const Number<modulo> &r) const {
        return value == r.value;
    }

    bool operator!=(const Number<modulo> &r) const {
        return value != r.value;
    }

    friend ostream &operator<<(ostream &os, const Number<modulo> &r) {
        return os << r.value;
    }
};

template <class T>
int gauss (vector < vector<T> > a, vector<T> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;
    cerr << n << " " << m << endl;
    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (a[i][col] != 0) {
                sel = i;
            }
        if (a[sel][col] == 0)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                T c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];

    for (int i=0; i<n; ++i) {
        T sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if (sum != a[i][m])
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return -1;
    return 1;
}
