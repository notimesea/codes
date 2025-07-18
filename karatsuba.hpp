#include <bits/stdc++.h>


template <class T>
struct karatsuba {
    static const int N = 1 << 22;
    T buffer[N];
    T * pos = buffer;

    T * allocate(const size_t & size) {
        memset(pos, 0, sizeof(T) * size);
        T * res = pos;
        pos += size;
        return res;
    }

    T * copyOf(const size_t & size, const T * src) {
        memcpy(pos, src, sizeof(T) * size);
        T * res = pos;
        pos += size;
        return res;
    }

    void clear(const size_t & size) {
        pos -= size;
    }

    T * multiply(const T *a, const T *b, size_t n) {
        if (n <= 32) {
            T * cur = allocate(2 * n);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    cur[i + j] += a[i] * b[j];
                }
            }
            return cur;
        }

        const size_t n2 = n / 2;

        T * res = allocate(2 * n);

        T * la = copyOf(n2, a);
        T * ra = copyOf(n2, a + n2);

        T * lb = copyOf(n2, b);
        T * rb = copyOf(n2, b + n2);

        T * l = multiply(la, lb, n2);

        T * r = multiply(ra, rb, n2);

        for (int i = 0; i < n2; ++i) {
            la[i] += ra[i];
            lb[i] += rb[i];
        }

        T * m = multiply(la, lb, n2);

        for (int i = 0; i < n; ++i) {
            res[i] += l[i];
            res[i + n] += r[i];
            res[i + n2] += m[i] - l[i] - r[i];
        }

        clear(5 * n);

        return res;
    }
};
