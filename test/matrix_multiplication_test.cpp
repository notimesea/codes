#include "../matrix_multiplication.hpp"
#include <cassert>
#include <iostream>

void test_matrix_multiplication() {
    // Test 1: Basic 2x2 multiplication
    {
        mat<2, 2> a, b;
        a.get(0, 0) = 1; a.get(0, 1) = 2;
        a.get(1, 0) = 3; a.get(1, 1) = 4;

        b.get(0, 0) = 5; b.get(0, 1) = 6;
        b.get(1, 0) = 7; b.get(1, 1) = 8;

        // a*b = [[1*5+2*7, 1*6+2*8], [3*5+4*7, 3*6+4*8]]
        //     = [[19, 22], [43, 50]]
        mat<2, 2> res = mul(a, b);

        assert(res.get(0, 0) == 19);
        assert(res.get(0, 1) == 22);
        assert(res.get(1, 0) == 43);
        assert(res.get(1, 1) == 50);
    }

    // Test 2: multiplication with non-square matrices
    {
        mat<2, 3> a;
        mat<3, 1> b;

        a.get(0, 0) = 1; a.get(0, 1) = 2; a.get(0, 2) = 3;
        a.get(1, 0) = 4; a.get(1, 1) = 5; a.get(1, 2) = 6;

        b.get(0, 0) = 7;
        b.get(1, 0) = 8;
        b.get(2, 0) = 9;

        // a*b = [[1*7+2*8+3*9], [4*7+5*8+6*9]]
        //     = [[7+16+27], [28+40+54]]
        //     = [[50], [122]]
        mat<2, 1> res = mul(a, b);
        assert(res.get(0, 0) == 50);
        assert(res.get(1, 0) == 122);
    }

    // Test 3: Matrix power
    {
        mat<2, 2> a; // Fibonacci matrix
        a.get(0, 0) = 1; a.get(0, 1) = 1;
        a.get(1, 0) = 1; a.get(1, 1) = 0;

        mat<2, 1> b; // Initial vector [F_1, F_0]
        b.get(0, 0) = 1;
        b.get(1, 0) = 0;

        // Calculate F_10
        // A^9 * [1, 0]^T = [F_10, F_9]^T = [55, 34]^T
        mat<2, 1> res = pw(a, b, 9);

        assert(res.get(0, 0) == 55);
        assert(res.get(1, 0) == 34);
    }

    std::cout << "Matrix multiplication tests passed!" << std::endl;
}

int main() {
    test_matrix_multiplication();
    return 0;
}
