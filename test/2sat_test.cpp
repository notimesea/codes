#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define all(x) (x).begin(), (x).end()

// Include the sat2 implementation
#include "../2sat"

int main() {
    // Satisfiable formula: x must be true.
    sat2 sat_true(1);
    sat_true.init();
    sat_true.add(0, 1); // not x -> x
    assert(sat_true.check());

    // Unsatisfiable formula: x must be true and false.
    sat2 sat_false(1);
    sat_false.init();
    sat_false.add(0, 1); // not x -> x
    sat_false.add(1, 0); // x -> not x
    assert(!sat_false.check());

    return 0;
}

/*
Compile and run:
    g++ -std=c++17 test/2sat_test.cpp -o 2sat_test
    ./2sat_test
*/
