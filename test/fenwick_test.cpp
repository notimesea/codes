#include "../fenwick.hpp"
#include <cassert>
#include <iostream>
#include <vector>

void test_fenwick_tree() {
    // Test case 1: Basic functionality
    fenwick<int> ft(10);
    ft.add(0, 5);
    ft.add(3, 2);
    ft.add(5, 3);

    assert(ft.get(0) == 5);
    assert(ft.get(1) == 5);
    assert(ft.get(2) == 5);
    assert(ft.get(3) == 7);
    assert(ft.get(4) == 7);
    assert(ft.get(5) == 10);
    assert(ft.get(9) == 10);

    // Test case 2: Another sequence of additions
    fenwick<long long> ft_ll(5);
    ft_ll.add(1, 100);
    ft_ll.add(1, 50);
    ft_ll.add(4, 200);

    assert(ft_ll.get(0) == 0);
    assert(ft_ll.get(1) == 150);
    assert(ft_ll.get(2) == 150);
    assert(ft_ll.get(3) == 150);
    assert(ft_ll.get(4) == 350);

    // Test case 3: All elements are 1
    int n = 100;
    fenwick<int> ft_ones(n);
    for (int i = 0; i < n; ++i) {
        ft_ones.add(i, 1);
    }
    for (int i = 0; i < n; ++i) {
        assert(ft_ones.get(i) == i + 1);
    }

    std::cout << "Fenwick tree tests passed!" << std::endl;
}

int main() {
    test_fenwick_tree();
    return 0;
}
