// Compile-time prime sieve using templates.
#include <bits/stdc++.h>

template<size_t a, size_t b>
struct Min {
    const static size_t value = a < b ? a : b;
};

template<size_t n, size_t low, size_t count>
struct FindFactor {
    const static size_t value = Min<FindFactor<n, low, count / 2>::value, FindFactor<n, low + count / 2, count - count / 2>::value>::value;
};

template<size_t n, size_t low>
struct FindFactor <n, low, 1> {
    const static size_t value = (n % low == 0) ? low : n;
};

template <size_t n> struct Sqrt {
    const static size_t value = size_t(sqrt(n + 0.5));
};

template<size_t n>
struct IsPrime {
    const static bool value = n > 1&& (n == 2 || (n % 2 != 0 && (n == 3 || FindFactor<n, size_t(2), Min<n - 2, Sqrt<n>::value-1>::value>::value == n)));
};

static_assert(IsPrime<1000003>::value, "1000000007 is prime");
static_assert(!IsPrime<1000000008>::value, "1000000008 is not prime");
