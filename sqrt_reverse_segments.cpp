#include <bits/stdc++.h>

#define clr(x) memset((x), 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define mp make_pair
#define in(x) int (x); input((x));
#define x first
#define y second
typedef int itn;

#define next next12345
#define prev prev12345
#define left lefdsf232
#define right rig43783
#define x1 x12345
#define y1 y12345

using namespace std;

template<typename T>
T gcd(T x, T y) {
    while (y > 0) {
        x %= y;
        swap(x, y);
    }
    return x;
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

typedef long double ld;
using ll = long long;
typedef unsigned long long ull;
typedef pair<int, int> PII;
const long double PI = 3.1415926535897932384626433832795L;

template<typename T>
inline void input(T &a) {
    static int ed;
    a = 0;
    while (!isdigit(ed = getchar()) && ed != '-') { }
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

template<typename T = int>
inline T nxt() {
    T res;
    input(res);
    return res;
}

mt19937 generator;

long long mod = 1000000007;

void fib(unsigned long long n, long long &x, long long &y) {
    if (n == 1) {
        x = 0, y = 1;
        return;
    }
    if (n & 1ull) {
        fib(n - 1, y, x);
        y += x;
        y %= mod;
    } else {
        long long a, b;
        fib(n / 2, a, b);
        x = (a * a + b * b) % mod;
        y = (2 * a + b) * b % mod;
    }
}

long long pw(long long a, long long n) {
    long long res = 1;
    while (n) {
        if (n & 1ll) {
            res = res * a % mod;
        }
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

const int N = 100000;
int pos[N];
int a[N];
int b[N];

struct segment {
    int left;
    int right;
    int rev;

    void split(int x, segment &l, segment &r) const {
        if (rev) x = len() - x;

        l.left = left;
        l.right = left + x;
        l.rev = 0;

        r.left = left + x;
        r.right = right;
        r.rev = 0;

        if (rev) {
            swap(l, r);
            l.rev = 1;
            r.rev = 1;
        }
    }
    int begin() const {
        if (!rev) {
            return left;
        } else {
            return right - 1;
        }
    }

    int end() const {
        if (!rev) {
            return right;
        } else {
            return left - 1;
        }
    }

    int step() const {
        return rev ? -1 : 1;
    }

    int len() const {
        return right - left;
    }

    bool contains(int pos) const {
        return pos >= left && pos < right;
    }

    int get(int pos) const {
        if (!rev) {
            return pos - left;
        } else {
            return right - pos - 1;
        }
    }

    int get2(int pos) const {
        if (!rev) {
            return left + pos;
        } else {
            return right - pos - 1;
        }
    }

    bool empty() const {
        return left == right;
    }

    void reverse() {
        rev ^= 1;
    }

    friend ostream & operator<<(ostream & os, const segment & s) {
        return os << "{" << s.left << ", " << s.rig43783 << ", " << s.rev << "}";
    }
};

list <segment> segs;

void rebuild() {
    int s = 0;
    for (const auto &seg : segs) {
        for (int i = seg.begin(); i != seg.end(); i += seg.step()) {
            b[s++] = a[i];
        }
    }
    for (int i = 0; i < s; ++i) {
        a[i] = b[i];
        pos[a[i]] = i;
    }
    segs.clear();
    segs.push_back(segment{0, s, 0});
}

void reverse(int l, int r) {
    list<segment>::iterator p1, p2;
    int s1 = 0;
    for (auto it = segs.begin(); it != segs.end(); ++it) {
        s1 += it->len();
        if (s1 > l) {
            s1 -= it->len();
            p1 = it;
            break;
        }
    }
    int s2 = 0;
    for (auto it = segs.begin(); it != segs.end(); ++it) {
        s2 += it->len();
        if (s2 >= r) {
            s2 -= it->len();
            p2 = it;
            break;
        }
    }
    //cout << s1 << " " << s2 << "\n";
    if (p1 == p2) {
        segment a, b, c, d;
        segment s = *p1;
        auto it = segs.erase(p1);
        s.split(l - s1, a, b);
        //cout << "A B " << a << " " << b << "\n";
        b.split(r - s2 - (l - s1), c, d);
        //cout << "C D " << c << " " << d << "\n";
        if (!d.empty()) {
            it = segs.insert(it, d);
        }
        c.reverse();
        it = segs.insert(it, c);
        if (!a.empty()) {
            it = segs.insert(it, a);
        }
    } else {
        {
            segment a, b;
            segment s = *p1;
            auto it = segs.erase(p1);
            s.split(l - s1, a, b);
            it = segs.insert(it, b);
            if (!a.empty()) {
                segs.insert(it, a);
            }
            p1 = it;
        }
        {
            segment a, b;
            segment s = *p2;
            auto it = segs.erase(p2);
            s.split(r - s2, a, b);
            if (!b.empty()) {
                it = segs.insert(it, b);
            }
            segs.insert(it, a);
            p2 = it;
        }
        reverse(p1, p2);
        for (auto it = p1; it != p2; ++it) {
            it->reverse();
        }
    }
}

int findElement(int elem) {
    int needPos = pos[elem];
    int s = 0;
    for (const auto & seg : segs) {
        if (seg.contains(needPos)) {
            return s + seg.get(needPos);
        }
        s += seg.len();
    }
    assert(false);
}

int findPos(int needPos) {
    int s = 0;
    for (const auto & seg : segs) {
        s += seg.len();
        if (s > needPos) {
            s -= seg.len();
            return a[seg.get2(needPos - s)];
        }
    }
    assert(false);
}

int main() {
    //#define int long
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
#define fname "race"
    //freopen(fname".in", "r", stdin);
    //freopen(fname".out", "w", stdout);
#endif

    int n = nxt();

    int q = nxt();

    for (int i = 0; i < n; ++i) {
        a[i] = i;
        pos[i] = i;
    }

    segs.push_back(segment{0, n, 0});

    const int MAGIC = 600;

    while (q--) {
        int t = nxt();
        if (t == 1) {
            int l = nxt() - 1, r = nxt();
            reverse(l, r);
        } else if (t == 2) {
            int x = nxt() - 1;
            printf("element %d is at position %d\n", x + 1, findElement(x) + 1);
        } else {
            int y = nxt() - 1;
            printf("element at position %d is %d\n", y + 1, findPos(y) + 1);
        }
        if (segs.size() > MAGIC) {
            rebuild();
        }
//        for (const auto & seg : segs) {
//            cout << seg << "\n";
//        }
    }


#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
}   
