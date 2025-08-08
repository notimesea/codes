#include <bits/stdc++.h>
#include "../ntt.hpp"


void test_ntt() {
    // Test 1: Forward and inverse transform
    {
        std::vector<ll> p = {1, 2, 3, 4, 0, 0, 0, 0}; // P(x) = 4x^3 + 3x^2 + 2x + 1
        std::vector<ll> p_orig = p;
        int n = p.size();

        fft(p, false); // Forward NTT
        fft(p, true);  // Inverse NTT

        for (int i = 0; i < n; ++i) {
            assert(p[i] == p_orig[i]);
        }
    }

    // Test 2: Polynomial multiplication
    {
        std::vector<ll> p1 = {1, 1, 0, 0}; // x + 1
        std::vector<ll> p2 = {2, 1, 0, 0}; // x + 2
        // Expected: (x+1)(x+2) = x^2 + 3x + 2 => {2, 3, 1, 0}

        fft(p1, false);
        fft(p2, false);

        std::vector<ll> res(4);
        for (int i = 0; i < 4; ++i) {
            res[i] = (p1[i] * p2[i]) % mod;
        }

        fft(res, true);

        assert(res[0] == 2);
        assert(res[1] == 3);
        assert(res[2] == 1);
        assert(res[3] == 0);
    }

    std::cout << "NTT tests passed!" << std::endl;
}

int main() {
    pre();
    test_ntt();
    return 0;
}
