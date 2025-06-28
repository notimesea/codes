# Competitive Programming Snippets

This repository contains standalone implementations of algorithms and data
structures commonly used in programming contests.

## Navigating the code

All source files live in the repository root. They are grouped below for
convenience.

### Data structures
- `fenwick.hpp` – binary indexed tree
- `hash_map.cpp` – open addressing hash table
- `bitset.hpp` – dynamic bitset implementation
- `segment_tree_interval_modification.hpp` – segment tree example
- `implicit_treap.hpp`, `persistent_cartesian.hpp` – treaps

### Graph algorithms
- `2sat.hpp` – boolean satisfiability solver
- `dinic.hpp` – maximum flow
- `hopcroft_karp.cpp` – bipartite matching
- `dominator_tree.hpp`, `euler_tour_link_cut.hpp`, `centroid_decomposition.hpp`

### Number theory & math
- `miller_rabin.hpp` – primality test
- `ntt.hpp` – number theoretic transform
- `karatsuba.hpp` – fast multiplication
- `compile_time_primes.hpp`, `prime_count.hpp`, `poly_inverse.hpp`
- `subset_convolution.hpp`, `sum_and_count_primes.cpp`

### String algorithms
- `aho_corasick_occurences.cpp` – Aho–Corasick automaton
- `suffix_array_tree.cpp`, `palindromic_tree.hpp`, `hash_suffixes.hpp`

### Miscellaneous
- `fast_input.hpp`, `fast_divider.hpp`, `hll.hpp`, etc.

The `test` directory contains simplified test versions of some snippets.

## Usage

Each file is self‑contained. Copy the desired snippet into your project or
include it directly when solving problems.
