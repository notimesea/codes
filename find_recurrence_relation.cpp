//#pragma GCC optimize("Ofast", "unroll-loops", "omit-frame-pointer", "inline") //Optimization flags
//#pragma GCC option("arch=native", "tune=native", "no-zero-upper") //Enable AVX
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4")  //Enable AVX

#include <memory>
#include <bits/stdc++.h>

#define clr(x) memset((x), 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define forn(i, n) for(int i = 0; i < (int)(n); ++i)
#define ford(i, n) for(int i = (int)(n) - 1; i >= 0; --i)
#define for1(i, n) for(int i = 1; i <= (int)(n); ++i)

using namespace std;

#ifndef LOCAL
#define cerr while(0) cerr
#endif

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
//typedef pair<long long, long long> pii;
typedef vector<long long> vll;
typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef int itn;
typedef unsigned int uint;

const ld PI = 3.1415926535897932384626433832795L;

template<class T>
bool uin(T &, const T &);

template<class T>
bool uax(T &, const T &);

template<class T>
T gcd(T, T);

template<class T>
T lcm(T, T);

template<class _T>
inline string tostr(const _T &);

template<typename T>
void input(T &);

template<typename T = long long>
T nxt();

bool checkp(long long);

template<typename T, typename N>
T pw(T a, N n, T m);

template<typename T>
T inv(T a, T p);

template<class _T>
_T sqr(const _T &x);

template<class T, class... Args>
inline auto make_vec(size_t n, Args &&... args) {
    if constexpr(sizeof...(args) == 1)
        return vector<T>(n, T(args...));
    else
        return vector(n, make_vec<T>(args...));
}

template<class... Args>
inline auto make_vec(size_t n, Args &&... args) {
    if constexpr(sizeof...(args) == 1)
        return vector(n, args...);
    else
        return vector(n, make_vec(args...));
}


int TTT;

void pre() {}

bool checkp(long long x) {
    if (x == 1) return true;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            return false;
        }
    }

    return true;
}

const ll mod = 1000000007;

template<long long modulo>
struct Number {
    long long value;

    Number<modulo>(const long long &v = 0) : value(((v % modulo) + modulo) % modulo) { }

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



template <long long mod>
struct LinearRecurrenceFinder {
    using num = Number<mod>;

    vector<num> extended(int n,
                         const vector< vector<num> >& coeffs, const vector<num>& terms) {

        vector<num> ret(max<int>(n + 1, terms.size()));
        copy(terms.begin(), terms.end(), ret.begin());
        const int order = coeffs.size() - 1;
        const int deg = coeffs[0].size() - 1;
        assert((int) terms.size() >= order);
        for (int m = terms.size(); m <= n; ++m) {
            num s = 0;
            for (int i = 1; i <= order; ++i) {
                int k = m - i;
                num t = ret[k];
                for (int d = 0; d <= deg; ++d) {
                    s = s + coeffs[i][d] * t;
                    t *= k;
                }
            }
            num denom = 0, mpow = 1;
            for (int d = 0; d <= deg; ++d) {
                denom = denom + mpow * coeffs[0][d];
                mpow = mpow * m;
            }
            ret[m] = s * (-1) / denom;
        }
        return ret;
    }

    vector< vector<num> > find_recurrence_relation(
            const vector<num>& terms, const int deg, bool verify=true) {

        const int n = terms.size();
        const int B = (n + 2) / (deg + 2); // number of blocks
        const int C = B * (deg + 1); // number of columns
        const int R = n - (B - 1); // number of rows
        assert(B >= 2); assert(R >= C - 1);

        auto error = [] (int order, int deg) {
            fprintf(stderr,
                    "Error: Could not find a recurrence relation "
                    "of order <= %d and degree <= %d.\n\n",
                    order, deg);
            assert(0);
        };

        vector< vector<num> > mat(R, vector<num>(C));
        for (int y = 0; y < R; ++y) {
            for (int b = 0; b < B; ++b) {
                num v = terms[y + b];
                for (int d = 0; d <= deg; ++d) {
                    mat[y][b * (deg + 1) + d] = v;
                    v *= y + b;
                }
            }
        }

        int rank = 0;
        for (int x = 0; x < C; ++x) {
            int pivot = -1;
            for (int y = rank; y < R; ++y) if (mat[y][x] != 0) {
                    pivot = y; break;
                }
            if (pivot < 0) break;
            if (pivot != rank) swap(mat[rank], mat[pivot]);
            num inv = mat[rank][x].reciprocal();
            for (int x2 = x; x2 < C; ++x2) mat[rank][x2] *= inv;
            for (int y = rank + 1; y < R; ++y) if (mat[y][x] != 0) {
                    num c = mat[y][x];
                    for (int x2 = x; x2 < C; ++x2) {
                        mat[y][x2] -= c * mat[rank][x2];
                    }
                }
            ++rank;
        }

        if (rank == C) error(B - 1, deg);

        for (int y = rank - 1; y >= 0; --y) if (mat[y][rank] != 0) {
                assert(mat[y][y] == 1);
                num c = mat[y][rank];
                for (int y2 = 0; y2 < y; ++y2) {
                    mat[y2][rank] -= c * mat[y2][y];
                }
            }

        int order = rank / (deg + 1);
        vector< vector<num> > ret(order + 1, vector<num>(deg + 1));
        ret[0][rank % (deg + 1)] = 1;
        for (int y = rank - 1; y >= 0; --y) {
            int k = order - y / (deg + 1), d = y % (deg + 1);
            ret[k][d] = mat[y][rank] * (-1);
        }

        if (verify) {
            auto extended_terms = extended(n - 1, ret,
                                           vector<num>(terms.begin(), terms.begin() + order));
            for (int i = 0; i < (int) terms.size(); ++i) {
                if (terms[i] != extended_terms[i]) error(B - 1, deg);
            }
        }

        auto verbose = [&] {
            int last = verify ? n - 1 : order + R - 1;
            fprintf(stderr,
                    "[ Found a recurrence relation ]\n"
                    "- order %d\n"
                    "- degree %d\n"
                    "- verified up to a(%d) (number of non-trivial terms: %d)\n",
                    order, deg, last, (last + 1) - ((deg + 2) * (order + 1) - 2)
            );
            fprintf(stderr, "{\n");
            for (int k = 0; k <= order; ++k) {
                fprintf(stderr, "  {");
                for (int d = 0; d <= deg; ++d) {
                    if (d) fprintf(stderr, ", ");
                    fprintf(stderr, "%lld", ret[k][d].value <= mod / 2 ? ret[k][d].value : ret[k][d].value - mod);
                }
                fprintf(stderr, "}%s\n", k == order ? "" : ",");
            }
            fprintf(stderr, "}\n\n");
        };
        verbose();

        return ret;
    }

    void show_extended_sequence(int n, const vector<num>& terms, int degree) {
        auto coeffs = find_recurrence_relation(terms, degree);
        auto extended_terms = extended(n, coeffs, terms);
        for (int i = 0; i < (int) extended_terms.size(); ++i) {
            cout << i << " " << extended_terms[i] << "\n";
        }
        cout << "\n";
    }
};

void solve(int _) {
    LinearRecurrenceFinder<mod> l;
//    l.show_extended_sequence(10, {4, 4, 5, 9, 27, 123, 723, 5040}, 2);
    // Factorial + 3
    l.show_extended_sequence(10, {4, 4, 5, 9, 27, 123, 723, 5043, 40323}, 3);
}


int main(int argc, char **argv) {
    ::TTT = 1;
    pre();

    for (int test = 1; test <= ::TTT; ++test) {
        solve(test);
    }

    return 0;
}

#ifdef LOCAL

struct timer {
    clock_t init;

    timer() {
        init = clock();
    }

    clock_t time() const {
        return clock() - init;
    }

    ~timer() {
        cerr << "Time elapsed: " << (double) (time()) / CLOCKS_PER_SEC * 1000 << " ms." << endl;
    }
};

#include <sys/resource.h>

struct init_str {
    timer t{};

    init_str() {
        freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);

        rlimit R{};
        getrlimit(RLIMIT_STACK, &R);
        R.rlim_cur = R.rlim_max;
        setrlimit(RLIMIT_STACK, &R);
    }

} init_global_;

#endif // LOCAL

//#define AUTO_MALLOC 0
#ifdef AUTO_MALLOC
namespace MALLOC {
    const size_t MAX_HEAP = 768 * 1000 * 1000;
    char buf[MAX_HEAP];
    size_t ptr;
}

void *operator new(size_t size) {
    void *result = MALLOC::buf + MALLOC::ptr;
    MALLOC::ptr += size;
    return result;
}

void operator delete(void *ptr) noexcept { /* DO NOTHING */ }

#endif //AUTO_MALLOC

template<typename T>
T gcd(T x, T y) {
    while (y > 0) {
        x %= y;
        swap(x, y);
    }
    return x;
}

template<class T>
T lcm(T a, T b) {
    return a / gcd(a, b) * b;
}

template<class _T>
inline _T sqr(const _T &x) {
    return x * x;
}

template<class _T>
inline string tostr(const _T &a) {
    ostringstream os("");
    os << a;
    return os.str();
}

template<typename T>
inline void input(T &a) {
    static int ed;
    a = 0;
    while (!isdigit(ed = getchar()) && ed != '-') {}
    char neg = 0;
    if (ed == '-') {
        neg = 1;
        ed = getchar();
    }
    while (isdigit(ed)) {
        a = 10 * a + ed - '0';
        ed = getchar();
    }
    if (neg) a = -a;
}

template<typename T>
inline T nxt() {
    T res;
    input(res);
    return res;
}


//bool checkp(long long v) {
//    if (v < 2) return false;
//    for (long long i = 2; i * i <= v; ++i) {
//        if (v % i == 0) {
//            return false;
//        }
//    }
//    return true;
//}

template<typename T, typename N>
T pw(T a, N n, T m) {
    T res = 1;
    while (n) {
        if (n & 1) {
            res = res * a % m;
        }
        a = a * a % m;
        n >>= 1;
    }
    return res;
}

template<typename T>
T inv(T a, T p) {
    T res = 1;
    while (a > 1) {
        res = res * (p - p / a) % p;
        a = p % a;
    }
    return res;
}

template<class T>
bool uin(T &a, const T &b) {
    if (b < a) {
        a = b;
        return true;
    }
    return false;
}

template<class T>
bool uax(T &a, const T &b) {
    if (b > a) {
        a = b;
        return true;
    }
    return false;
}






