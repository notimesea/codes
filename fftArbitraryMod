int MOD = 1000000007;

#define sz(x) ((x).size())

void addmod(int &x, int y, int mod) {
    (x += y) >= mod && (x -= mod);
}

int mulmod(int x, int y, int mod) {
    return x * 1ll * y % mod;
}


typedef double D;
const int N = 1 << 17;

struct C {
    D x, y;

    C() {}

    C(D x, D y) : x(x), y(y) {}

    C operator+(const C &r) const {
        return C(x + r.x, y + r.y);
    }

    C operator-(const C &r) const {
        return C(x - r.x, y - r.y);
    }

    C operator*(const C &r) const {
        return C(x * r.x - y * r.y, y * r.x + x * r.y);
    }

    C &operator/=(const D &r) {
        x /= r;
        y /= r;
        return *this;
    }
};

C PW[N];
C IPW[N];
C CPW[N];


void initFFT() {
    for (int i = 0; i < N; ++i) {
        D ang = i * 2 * PI / N;
        D co = cosl(ang);
        D si = sinl(ang);
        PW[i] = C(co, si);
        IPW[i] = C(co, -si);
    }
}

void fft(C *a, int n, bool inv) {
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        while (j >= bit) {
            j -= bit;
            bit >>= 1;
        }
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2, shift = N >> 1; len <= n; len <<= 1, shift >>= 1) {
        int len2 = len >> 1;
        for (int j = 0; j < len2; ++j) {
            CPW[j] = inv ? IPW[j * shift] : PW[j * shift];
        }
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < len2; ++j) {
                C u = a[i + j];
                C v = a[i + j + len2] * CPW[j];
                a[i + j] = u + v;
                a[i + j + len2] = u - v;
            }
        }
    }
    if (inv) {
        for (int i = 0; i < n; ++i) {
            a[i] /= n;
        }
    }
}

C A[N];
C B[N];

vi mult(const vi &a, const vi &b) {
    int n = 1;
    while (n < (int) (a.size() + b.size()) - 1) {
        n <<= 1;
    }
    assert(n <= N);
    memset(A, 0, n * sizeof(C));
    memset(B, 0, n * sizeof(C));
    for (size_t i = 0; i < a.size(); ++i) {
        A[i].x = a[i];
    }
    for (size_t i = 0; i < b.size(); ++i) {
        B[i].x = b[i];
    }
    fft(A, n, false);
    fft(B, n, false);
    for (int i = 0; i < n; ++i) {
        A[i] = A[i] * B[i];
    }
    fft(A, n, true);
    vi c(n);
    for (int i = 0; i < n; ++i) {
        c[i] = llround(A[i].x) % MOD;
    }
    c.resize(a.size() + b.size() - 1);
    return c;
}


vi multmod(const vi &a, const vi &b) {
    if (a.size() <= 64) {
        vi res(a.size() + b.size() - 1);
        forn(i, sz(a)) {
            forn(j, sz(b)) {
                addmod(res[i + j], mulmod(a[i], b[j], MOD), MOD);
            }
        }
        return res;
    }
    // a = a0 + sqrt(MOD) * a1
    // a = a0 + base * a1
    int base = (int) sqrtl(MOD);

    vi a0(sz(a)), a1(sz(a));
    forn(i, sz(a)) {
        a0[i] = a[i] % base;
        a1[i] = a[i] / base;
        assert(a[i] == a0[i] + base * a1[i]);
    }

    vi b0(sz(b)), b1(sz(b));
    forn(i, sz(b)) {
        b0[i] = b[i] % base;
        b1[i] = b[i] / base;
        assert(b[i] == b0[i] + base * b1[i]);
    }

    vi a01 = a0;
    forn(i, sz(a)) {
        addmod(a01[i], a1[i], MOD);
    }

    vi b01 = b0;
    forn(i, sz(b)) {
        addmod(b01[i], b1[i], MOD);
    }

    vi C = mult(a01, b01);  // 1
    vi a0b0 = mult(a0, b0); // 2
    vi a1b1 = mult(a1, b1); // 3

    vi mid = C;
    forn(i, sz(mid)) {
        addmod(mid[i], -a0b0[i] + MOD, MOD);
        addmod(mid[i], -a1b1[i] + MOD, MOD);
    }

    vi res = a0b0;
    forn(i, sz(mid)) {
        addmod(res[i], mulmod(base, mid[i], MOD), MOD);
    }

    base = mulmod(base, base, MOD);
    forn(i, sz(mid)) {
        addmod(res[i], mulmod(base, a1b1[i], MOD), MOD);
    }

    return res;
}
