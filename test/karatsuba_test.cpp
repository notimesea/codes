#include "../karatsuba.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <numeric>

void test_karatsuba() {
    static karatsuba<long long> k;

    // Test case 1: Simple multiplication
    {
        std::vector<long long> p1 = {1, 1}; // x + 1
        std::vector<long long> p2 = {2, 1}; // x + 2
        // Expected: (x+1)(x+2) = x^2 + 3x + 2 => {2, 3, 1}

        long long* res = k.multiply(p1.data(), p2.data(), 2);

        assert(res[0] == 2);
        assert(res[1] == 3);
        assert(res[2] == 1);
        k.clear(4);
    }

    // Test case 2: Higher degree
    {
        std::vector<long long> p1 = {1, 2, 1}; // x^2 + 2x + 1
        std::vector<long long> p2 = {1, 2, 1}; // x^2 + 2x + 1
        // Expected: (x+1)^2 * (x+1)^2 = (x+1)^4 = x^4 + 4x^3 + 6x^2 + 4x + 1 => {1, 4, 6, 4, 1}

        long long* res = k.multiply(p1.data(), p2.data(), 3);

        // The result size will be 2*n, so 6. We check up to degree 4.
        assert(res[0] == 1);
        assert(res[1] == 4);
        assert(res[2] == 6);
        assert(res[3] == 4);
        assert(res[4] == 1);
        k.clear(6);
    }

    // Test case 3: Larger multiplication needed for recursion
    {
        // This will trigger the recursive step since n=40 > 32
        const int n = 40;
        std::vector<long long> p1(n, 1);
        std::vector<long long> p2(n, 1);

        long long* res = k.multiply(p1.data(), p2.data(), n);

        std::vector<long long> expected(2 * n, 0);
        for(int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                expected[i+j] += p1[i] * p2[j];
            }
        }

        for(int i = 0; i < 2 * n - 1; ++i) {
            assert(res[i] == expected[i]);
        }
        k.clear(2 * n);
    }

    std::cout << "Karatsuba tests passed!" << std::endl;
}

int main() {
    test_karatsuba();
    return 0;
}
