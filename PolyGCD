#include <bits/stdc++.h>
#define clr(x) memset((x), 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define mp make_pair
#define For(i, st, en) for(int i=(st); i<=(int)(en); i++)
#define Ford(i, st, en) for(int i=(st); i>=(int)(en); i--)
#define forn(i, n) for(int i=0; i<(int)(n); i++)
#define ford(i, n) for(int i=(n)-1; i>=0; i--)
#define fori(it, x) for (__typeof((x).begin()) it = (x).begin(); it != (x).end(); it++)
#define in(x) int (x); input((x));
#define x first
#define y second
#define less(a,b) ((a) < (b) - EPS)
#define more(a,b) ((a) > (b) + EPS)
#define eq(a,b) (fabs((a) - (b)) < EPS)
#define remax(a, b) ((a) = (b) > (a) ? (b) : (a))
#define remin(a, b) ((a) = (b) < (a) ? (b) : (a))
using namespace std;
typedef long double ld; template <class _T> inline _T sqr(const _T& x) {return x * x;} template <class _T> inline string tostr(const _T& a) {ostringstream os(""); os << a; return os.str();} const ld PI = 3.1415926535897932384626433832795L; const double EPS = 1-9; char TEMPORARY_CHAR; typedef long long ll; typedef unsigned long long ull; typedef set < int > SI; typedef vector < int > VI; typedef vector < vector < int > > VVI; typedef map < string, int > MSI; typedef pair < int, int > PII; const int INF = 1e9; inline void input(int &a) {a = 0; while (((TEMPORARY_CHAR = getchar()) > '9' || TEMPORARY_CHAR < '0') && (TEMPORARY_CHAR != '-')){} char neg = 0; if (TEMPORARY_CHAR == '-') {neg = 1; TEMPORARY_CHAR = getchar();} while (TEMPORARY_CHAR <= '9' && TEMPORARY_CHAR >= '0') {a = 10 * a + TEMPORARY_CHAR - '0'; TEMPORARY_CHAR = getchar();} if (neg) a = -a;} inline void out(int a) {if (!a) putchar('0'); if (a < 0) {putchar('-'); a = -a;} char s[10]; int i; for(i = 0; a; ++i) {s[i] = '0' + a % 10; a /= 10;} ford(j, i) putchar(s[j]);} inline int nxt() {in(ret); return ret;}
 
using namespace std;
#define ld double
 
typedef vector<short> poly;
 
int MOD = 1009;
 
struct comp
{
    ld x, y;
    comp():x(0), y(0){}
    comp(ld _x):x(_x), y(0){}
    comp(ld _x, ld _y):x(_x), y(_y){}
    inline comp operator+(const comp & r)
    {
        return comp(x + r.x, y + r.y);
    }
    inline comp operator-(const comp & r)
    {
        return comp(x - r.x, y - r.y);
    }
    inline comp operator*(const comp & r)
    {
        return comp(x * r.x - y * r.y, x * r.y + y * r.x);
    }
    inline void operator/=(const ld & r)
    {
        x /= r;
        y /= r;
    }
};
 
int N;
int log_2;
 
int n;
 
comp *A, *B;
 
int * r;
comp * powers[2];
 
inline void prec()
{
    ld mn0 = 2 * PI / N, mn1 = -2 * PI / N;
    for(int i = 0; i < N; ++i)
    {
        powers[0][i] = comp(cos(mn0 * i), sin(mn0 * i));
        powers[1][i] = comp(cos(mn1 * i), sin(mn1 * i));
    }
}
 
void fft (comp a[], int invert = 0)
{
    for (int i=1, j=0; i<n; ++i)
    {
        int bit = n >> 1;
        for (; j >= bit; bit >>= 1)
            j -= bit;
        j += bit;
        if (i < j)
            swap (a[i], a[j]);
    }
 
    for (int len = 2, shift = N >> 1; len <= n; len <<= 1, shift >>= 1)
    {
        int len2 = len >> 1;
 
        for (int i = 0; i < n; i += len)
        {
            for (int j = 0, p = 0; j < len2; ++j, p += shift)
            {
                comp u = a[i + j],  v = a[i + j + len2] * powers[invert][p];
                a[i + j] = u + v;
                a[i + j + len2] = u - v;
            }
        }
    }
    if (invert)
        for (int i = 0; i < n; ++i)
            a[i] /= n;
}
 
void setN(int a, int b)
{
    a = a + b;
    n = 1;
    while(n < a)
        n *= 2;
}
 
poly mul(const poly &a, const poly &b)
{
    setN(a.size(), b.size());
 
    memset(A, 0, sizeof(comp) * n);
    memset(B, 0, sizeof(comp) * n);
 
    for (int i = 0; i < (int)a.size(); ++i)
    {
        A[i].x = a[i];
    }
    for (int i = 0; i < (int)b.size(); ++i)
    {
        B[i].x = b[i];
    }
 
    fft(A);
    fft(B);
 
    for (int i = 0; i < n; ++i)
    {
        A[i] = A[i] * B[i];
    }
 
    fft(A, 1);
 
    poly ret(a.size() + b.size());
 
    for (int i = 0; i < (int)a.size() + (int)b.size(); ++i)
    {
        int cur = (A[i].x + 0.5);
        ret[i] = cur % MOD;
        if (ret[i] < 0)
            ret[i] += MOD;
    }
 
    while(ret.size() > 0 && ret.back() == 0)
        ret.pop_back();
 
    return ret;
}
 
poly add(const poly &a, const poly &b)
{
    poly ret(max(a.size(), b.size()));
 
    for (size_t i=0; i < ret.size(); ++i)
    {
        ret[i] = (i < b.size() ? b[i] : 0) + (i < a.size() ? a[i] : 0);
        if (ret[i] >= MOD)
            ret[i] -= MOD;
    }
    while (ret.size() > 0 && ret.back() == 0)
        ret.pop_back();
    return ret;
}
 
poly sub(const poly &a, const poly &b)
{
    poly ret(max(a.size(), b.size()));
 
    for (size_t i=0; i<ret.size(); ++i)
    {
        ret[i] = (i < a.size() ? a[i] : 0) + (i < b.size() ? (MOD - b[i]) : 0);
        if (ret[i] >= MOD)
            ret[i] -= MOD;
    }
    while (ret.size() > 0 && ret.back() == 0)
        ret.pop_back();
    return ret;
}
 
poly mul(const poly &a, int mul)
{
    poly res = a;
    for(size_t i = 0; i < a.size(); ++i)
    {
        res[i] = (res[i] * mul) % MOD;
    }
    while (res.size() > 0 && res.back() == 0)
        res.pop_back();
    return res;
}
 
short inv[2000];
 
void calc_inv()
{
    inv[1] = 1;
    for (int i = 2; i < MOD; ++i)
    {
        inv[i] = (MOD - (MOD / i) * inv[MOD % i] % MOD) % MOD;
        //assert(inv[i] > 0);
    }
}
 
poly Reciprocal(const poly::iterator & l, const poly::iterator & r)
{
    int k = distance(l, r);
    //assert(k > 0);
    if (k == 1)
    {
        //assert(*l > 0);
        //assert(*l < MOD);
        return poly(1, inv[*l]);
    }
    else
    {
        poly q = Reciprocal(l + k / 2, r);
        poly z = mul(q, poly(l, r));
        poly t = poly(3 * k / 2 - 1);
        t.back() = 2;
        z = sub(t, z);
        poly v = mul(q, z);
        v.resize(max((int)v.size(), k - 2));
        return poly(v.begin() + k - 2, v.end());
    }
}
 
poly div(poly u, poly v)
{
 
    int mm = u.size();
    int nn = v.size();
    //assert(nn > 0);
    /*if(mm - nn > 5)
    {
        cerr << nn << " " << mm << endl;
        assert(false);
    }*/
    if (mm == 0)
    {
        return poly();
    }
    if (mm < nn)
    {
        return poly();
    }
    if (nn == 1)
    {
        //assert(v[0] > 0);
        //assert(v[0] < MOD);
        return mul(u, inv[v[0]]);
    }
    int NN = 1;
    while(NN < nn)
        NN *= 2;
    int delta = NN - nn;
    u.resize(mm + NN - nn);
    v.resize(NN);
    for(int i = (int)u.size() - 1; i >= 0; --i)
    {
        if (i >= delta)
            u[i] = u[i - delta];
        else
            u[i] = 0;
    }
    for(int i = (int)v.size() - 1; i >= 0; --i)
    {
        if (i >= delta)
            v[i] = v[i - delta];
        else
            v[i] = 0;
    }
 
    mm += delta;
    nn += delta;
    //assert(v.back() > 0);
    /*for(int i = 0; i < (int)v.size(); ++i)
    {
        cerr << v[i] << " ";
    }
    cerr << endl;
    */
    //assert(__builtin_popcount(v.size()) == 1);
    poly s = Reciprocal(v.begin(), v.end());
 
    poly res = mul(u, s);
    //assert(res.size() >= 2 * nn - 2);
    res = poly(res.begin() + 2 * nn - 2, res.end());
    if (mm < 2 * nn)
    {
        return res;
    }
    else
    {
        poly dva = poly(2 * nn - 1);
        dva.back() = 1;
        poly t = sub(dva, mul(s, v));
        poly z = mul(u, t);
        //assert(z.size() >= 2 * nn - 2);
        z = poly(z.begin() + 2 * nn - 2, z.end());
        poly d = div(z, v);
        return add(res, d);
    }
}
 
 
struct matrix
{
    poly A, B, C, D;
};
 
 
matrix operator*(const matrix & l, const matrix & r)
{
    poly P1 = mul(add(l.A, l.D), add(r.A, r.D));
    poly P2 = mul(add(l.C, l.D), r.A);
    poly P3 = mul(l.A, sub(r.B, r.D));
    poly P4 = mul(l.D, sub(r.C, r.A));
    poly P5 = mul(add(l.A, l.B), r.D);
    poly P6 = mul(sub(l.C, l.A), add(r.A, r.B));
    poly P7 = mul(sub(l.B, l.D), add(r.C, r.D));
    matrix res;
    res.A = add(P1, add(P7, sub(P4, P5)));
    res.B = add(P3, P5);
    res.C = add(P2, P4);
    res.D = add(sub(P1, P2), add(P3, P6));
    return res;
}
 
matrix HGCD(const poly & a0, const poly & a1)
{
    //assert(a0.empty() || a0.back() > 0);
    //assert(!a1.empty());
    //assert(a1.empty() || a1.back() > 0);
    int d0 = (int)a0.size() - 1;
    int d1 = (int)a1.size() - 1;
    int m = (d0 + 1) / 2;
    if (d1 < m)
    {
        matrix res;
        res.A = poly(1, 1);
        res.B = poly();
        res.C = poly();
        res.D = poly(1, 1);
        return res;
    }
    else
    {
        matrix R = HGCD(poly(a0.begin() + m, a0.end()), poly(a1.begin() + m, a1.end()));
        poly d = add(mul(R.A, a0), mul(R.B, a1));
        poly e = add(mul(R.C, a0), mul(R.D, a1));
        //cerr << a0.size() << " " << a1.size() << endl;
        //cerr << a0.size() << " " << a1.size() << " " << m << endl;
        //assert(e.size() > 1 || (e.size() == 1 && e.back() == 0));
        //assert(e.size() > 0);
        if ((int)e.size() - 1 < m)
            return R;
        poly q = div(d, e);
 
        poly f = sub(d, mul(e, q));
 
        int l = (int)e.size() - 1;
        //assert(l - m < (m1 + 1) / 2);
        int k = (2 * m - l);
 
        e.resize(max((int)e.size(), k));
        //assert((int)e.size() >= k);
        f.resize(max((int)f.size(), k));
        //assert((int)f.size() >= k);
        e = poly(e.begin() + k, e.end());
        f = poly(f.begin() + k, f.end());
        //assert(e.size() > 0);
        //assert(e.size() > f.size());
        matrix S = HGCD(e, f);
 
        matrix T;
        T.A = S.B;
        T.B = sub(S.A, mul(q, S.B));
        T.C = S.D;
        T.D = sub(S.C, mul(q, S.D));
 
        return T * R;
    }
}
 
 
poly GCD(const poly & a0, const poly & a1)
{
    poly q = div(a0, a1);
    poly mod = sub(a0, mul(q, a1));
    if (mod.empty())
    {
        return a1;
    }
    else
    {
        matrix R = HGCD(a0, a1);
        poly b0 = add(mul(R.A, a0), mul(R.B, a1));
        poly b1 = add(mul(R.C, a0), mul(R.D, a1));
        if (b0.size() < b1.size())
            b0.swap(b1);
        if (b1.empty())
            return b0;
        q = div(b0, b1);
        mod = sub(b0, mul(q, b1));
        if (mod.empty())
        {
            return b1;
        }
        else
        {
            return GCD(b1, mod);
        }
    }
}
 
void init()
{
    N = (1 << 17);
    log_2 = 17;
    powers[0] = new comp[N];
    powers[1] = new comp[N];
    A = new comp[N];
    B = new comp[N];
    r = new int[N];
    prec();
}
 
int main()
{
    init();
    in(t);
    while(t--)
    {
        MOD = 1009;
        calc_inv();
        in(n);
        poly a(n);
        int first = -1;
        for(int i = 0; i < n; ++i)
        {
            a[i] = nxt();
            if (a[i])
                first = i;
            a[i] = (a[i] + MOD) % MOD;
        }
        poly d(n);
        if (first == -1)
        {
            puts("YES");
            continue;
        }
        for(int i = 0; i < n; ++i)
        {
            d[i] = a[(i - (n - 1 - first) + n) % n];
        }
        poly b(n + 1);
        b[0] = MOD - 1;
        b[n] = 1;
        poly c = GCD(b, d);
        if (c.size() != 1)
        {
            puts("YES");
        }
        else
        {
            puts("NO");
        }
    }
 
    return 0;
}
