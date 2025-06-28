//
// Created by Evgeny Savinov on 09/01/2017.
//

#include <bits/stdc++.h>

#pragma GCC optimize ("O3")

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

//template <typename T = int>
class range {
    using type = int;
public:
    class iterator {
        friend class range;

    public:
        using difference_type = range::type;
        using value_type = range::type;
        using pointer = const range::type *;
        using reference = const range::type &;
        using iterator_category = std::random_access_iterator_tag;

        value_type operator*() const { return i_; }

        const iterator &operator++() {
            ++i_;
            return *this;
        }

        iterator operator++(int) {
            iterator copy(*this);
            ++i_;
            return copy;
        }

        const iterator &operator--() {
            --i_;
            return *this;
        }

        iterator operator--(int) {
            iterator copy(*this);
            --i_;
            return copy;
        }

        difference_type operator-(const iterator &other) const { return i_ - other.i_; }

        iterator operator+(const difference_type &delta) const { return iterator(i_ + delta); }

        iterator &operator+=(const difference_type &delta) {
            i_ += delta;
            return *this;
        }

        iterator operator-(const difference_type &delta) const { return iterator(i_ - delta); }

        iterator &operator-=(const difference_type &delta) {
            i_ -= delta;
            return *this;
        }

        bool operator==(const iterator &other) const { return i_ == other.i_; }

        bool operator!=(const iterator &other) const { return i_ != other.i_; }

    protected:
        iterator(const value_type &start) : i_(start) {}

    private:
        value_type i_;
    };

    iterator begin() const { return begin_; }

    iterator end() const { return end_; }

    range(const type &begin, const type &end) : begin_(begin), end_(end) {}

    range(const type &end) : begin_(0), end_(end) {}

private:
    iterator begin_;
    iterator end_;
};

template<typename T = long long>
T nxt();

bool checkp(long long);

template<typename T>
T pw(T a, T n, T p);

template<typename T>
T inv(T a, T p);

template<class _T>
_T sqr(const _T &x);

class range;

mt19937_64 gen;

int TTT;

const ll mod = 1000000007;

void pre() {}

struct SuffixArray {
    int *str;
    int *sa;
    int *ra;
    int *lcp;
    int *lgt;
    int **rmq;
    int n;

    SuffixArray() : str(0), sa(0), ra(0), lcp(0), lgt(0), rmq(0), n(0) {}

    int get(int pos) const {
        assert(pos < n);
        return str[pos];
    }

    void init(const vector<int> &s) {
        destroy();

        n = (int) s.size();
        str = new int[n];
        for (int i = 0; i < n; ++i) str[i] = s[i];
        __init();
    }

    void init(const string &s) {
        destroy();

        n = (int) s.length();
        str = new int[n];
        for (int i = 0; i < n; ++i) str[i] = s[i];
        __init();
    }

    void __init() {
        initSa();
        initLcp();
    }

    void initSa() {
        sa = new int[n];
        ra = new int[n];
        int *s = new int[n];
        int *c = new int[n];
        int *cl = new int[n];
        int *cnt = new int[n];
        for (int i = 0; i < n; ++i) {
            cl[i] = str[i];
            sa[i] = n - i - 1;
        }
        stable_sort(sa, sa + n, [&](int l, int r) { return str[l] < str[r]; });
        for (int len = 1; len < n; len <<= 1) {
            memcpy(c, cl, n * sizeof(int));
            memcpy(s, sa, n * sizeof(int));
            for (int i = 0; i < n; ++i) cnt[i] = i;
            int len2 = len >> 1;
            for (int i = 0; i < n; ++i) {

                if (i > 0 && c[sa[i]] == c[sa[i - 1]] && sa[i - 1] + len < n &&
                    c[sa[i] + len2] == c[sa[i - 1] + len2]) {
                    cl[sa[i]] = cl[sa[i - 1]];
                } else {
                    cl[sa[i]] = i;
                }
            }
            for (int i = 0; i < n; ++i) {
                int s1 = s[i] - len;
                if (s1 >= 0) {
                    sa[cnt[cl[s1]]++] = s1;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            ra[sa[i]] = i;
        }
        delete[] s;
        delete[] c;
        delete[] cl;
        delete[] cnt;
    }

    void initLcp() {
        lcp = new int[n];
        for (int i = 0, h = 0; i < n; ++i) {
            if (ra[i] < n - 1) {
                for (int j = sa[ra[i] + 1]; max(i, j) + h < n && str[i + h] == str[j + h]; ++h);
                lcp[ra[i]] = h;
                h = max(0, h - 1);
            } else {
                lcp[ra[i]] = 0;
            }
        }
        lgt = new int[n + 1];
        lgt[0] = lgt[1] = 0;
        for (int i = 2; i <= n; ++i) lgt[i] = lgt[i >> 1] + 1;
        rmq = new int *[lgt[n] + 1];
        for (int i = 0; i <= lgt[n]; ++i) {
            rmq[i] = new int[n];
        }
        for (int i = 0; i + 1 < n; ++i) {
            rmq[0][i] = lcp[i];
        }
        for (int l = 1; (1 << l) < n; ++l) {
            for (int i = 0; i + (1 << l) <= n; ++i) {
                rmq[l][i] = min(rmq[l - 1][i], rmq[l - 1][i + (1 << (l - 1))]);
            }
        }
    }

    int getLcpForSuffixes(int l, int r) {
        if (l == r) return n - l;
        l = ra[l];
        r = ra[r];
        if (l > r) swap(l, r);
        --r;
        int j = lgt[r - l];
        return min(rmq[j][l], rmq[j][r - (1 << j) + 1]);
    }

    void destroy() {
        if (str) delete[] str, str = 0;
        if (sa) delete[] sa, sa = 0;
        if (ra) delete[] ra, ra = 0;
        if (lgt) {
            for (int i = 0; i <= lgt[n]; ++i) {
                delete[] rmq[i], rmq[i] = 0;
            }
            delete[] lgt, lgt = 0;
            delete[] rmq, rmq = 0;
        }
    }

    ~SuffixArray() {
        destroy();
    }
} sa;

struct Substring {
    int s;
    int len;

    int lcp(const Substring &r) const {
        return min(len, min(r.len, sa.getLcpForSuffixes(s, r.s)));
    }

    int get(int pos) const {
        if (pos >= len) {
            return -1;
        } else {
            return sa.get(s + pos);
        }
    }

    bool operator<(const Substring &r) const {
        int lc = lcp(r);
        return get(lc) < r.get(lc);
    }

    bool operator==(const Substring &r) const {
        int lc = lcp(r);
        return lc == len && lc == r.len;
    }
};

struct Node {
    vector<Node *> children;
    Node *p;
    int len;
    int cnt;

    Node() {
        p = nullptr;
        len = 0;
        cnt = 0;
    }
};


ll solve(Node *root, ll M) {
    ll res = root->cnt;
    if (root->children.empty()) {
        res += 1;
    } else {
        ll q = 1;
        for (auto c : root->children) {
            q = q * solve(c, M) % M;
        }
        res += q;
        res %= M;
    }
    return res;
}

ll solve(vector<Substring> x, ll M) {
    sort(all(x));

    auto root = new Node();
    vector<Node *> st;
    st.pb(root);
    Substring last = Substring{0, 0};

//    for (auto p : x) {
//        cerr << p.s << " " << p.len << endl;
//    }

    for (auto s : x) {
        int lcp = s.lcp(last);
//        cerr << lcp << endl;
        Node *lastP = nullptr;

        while (st.back()->len > lcp) {
            lastP = st.back();
            st.pop_back();
            assert(!st.empty());
        }

        if (st.back()->len < lcp) {
            auto to_add = new Node();
            to_add->len = lcp;
            to_add->p = st.back();
            if (lastP) {
                st.back()->children.pop_back();
                to_add->children.push_back(lastP);
            }
            st.back()->children.push_back(to_add);
            st.push_back(to_add);
        }

        if (st.back()->len < s.len) {
            auto to_add = new Node();
            to_add->len = s.len;
            to_add->p = st.back();

            st.back()->children.push_back(to_add);
            st.push_back(to_add);
        }
        st.back()->cnt++;

        last = s;
    }

    return solve(root, M);
}

void solve(int test) {
    int n = nxt();
    int q = nxt();
    string s;
    cin >> s;

    sa.init(s);

    while (q--) {
        int k = nxt();
        vector<Substring> x;
        ll M = nxt();
        while (k--) {
            int s = nxt() - 1;
            int len = nxt() - s;
            auto ss = Substring{s, len};

            x.push_back(ss);
        }
        cout << solve(x, M) << "\n";
    }
}

#undef int

int main(int argc, char **argv) {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
#else
#define fname "sequence"
    //freopen(fname".in", "r", stdin);
    //freopen(fname".out", "w", stdout);
#endif
    pre();
    ::TTT = 1;
#ifdef LOCAL
#else
#endif

    for (int test = 1; test <= ::TTT; ++test) {
        solve(test);
    }

#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
}


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

void myassert(bool v) {
    assert(v);
//cout << "FAIL\n";
//exit(0);
}

mt19937 generator;

bool checkp(long long v) {
    if (v < 2) return false;
    for (long long i = 2; i * i <= v; ++i) {
        if (v % i == 0) {
            return false;
        }
    }
    return true;
}

template<typename T>
T pw(T a, T n, T m) {
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
