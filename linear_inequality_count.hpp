#include <bits/stdc++.h>
using ll = long long;

template <typename c_type, typename o_type>
o_type get_count(c_type A, c_type B, o_type C, o_type X);

template <typename o_type>
inline o_type s1(o_type X) {
  if (X % 2 == 0) {
    return X / 2 * (X + 1);
  } else {
    return (X + 1) / 2 * X;
  }
}

// A * x + B * y <= C
// 0 <= x <= X
template <typename c_type, typename o_type>
inline o_type get_count(c_type A, c_type B, o_type C) {
  assert(A > 0 && B > 0);
  if (C < 0) return 0;
  if (A < B) swap(A, B);

  const c_type U = A / B;
  const c_type V = A % B;

  return get_count(V, B, C, C / A) - U * s1(C / A);
}


// A * x + B * y <= C
// 0 <= x <= X
template <typename c_type, typename o_type>
inline o_type get_count(c_type A, c_type B, o_type C, o_type X) {
  assert(B > 0 && A >= 0);

  if (C < 0) return 0;
  if (A == 0) {
    return (C / B + 1) * (X + 1);
  }

  if (C / A <= X) {
    return get_count(A, B, C);
  }

  o_type Y = (C - A * X) / B;
  C -= Y * B;
  assert(A * X + B > C);

  return (X + 1) * Y + get_count(A, B, C) - max(o_type(0), C / A - X);
}

// A * x + B * y <= C
// 0 <= x <= X, 0 <= y <= Y
template <typename c_type, typename o_type>
o_type get_count(c_type A, c_type B, o_type C, o_type X, o_type Y) {
  assert(A >= 0 && B >= 0);
  if (C < 0) return 0;

  if (A == 0 || B == 0) {
    if (A) X = min(X, C / A);
    if (B) Y = min(Y, C / B);
    return (X + 1) * (Y + 1);
  }

  if (C / A > X && C / B > Y) {
    return get_count(A, B, C, X) + get_count(B, A, C, Y) - get_count(A, B, C) + get_count(A, B, C - A * (X + 1) - B * (Y + 1));
  }
  if (C / A > X) {
    return get_count(A, B, C, X);
  }
  if (C / B > Y) {
    return get_count(B, A, C, Y);
  }

  return get_count(A, B, C);
}


ll stupid_count(ll A, ll B, ll C, ll X, ll Y) {
  ll res = 0;
  for (ll x = 0; x <= X; ++x) {
    for (ll y = 0; y <= Y; ++y) {
      if (A * x + B * y <= C) {
        res++;
      }
    }
  }
  return res;
}
