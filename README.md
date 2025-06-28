# Competitive Programming Snippets

This repository contains standalone implementations of algorithms and data
structures commonly used in programming contests.

## Navigating the code

All source files live in the repository root. They are grouped below for
convenience.

### Data structures
- `fenwick` – binary indexed tree
- `HashMap` – open addressing hash table
- `Bitset` – dynamic bitset implementation
- `segmentTreeIntervalModification` – segment tree example
- `implicitTreap`, `persistentCartesian` – treaps

### Graph algorithms
- `2sat` – boolean satisfiability solver
- `dinic` – maximum flow
- `hopcroftKarp` – bipartite matching
- `dominatorTree`, `eulerTourLinkCut`, `centroidDecomposition`

### Number theory & math
- `MillerRabin` – primality test
- `ntt` – number theoretic transform
- `karatsuba` – fast multiplication
- `compileTimePrimes`, `primeCount`, `poly_inverse`
- `subsetConvolution`, `sumAndCountPrimes`

### String algorithms
- `AhoCorasickOccurences` – Aho–Corasick automaton
- `suffixArrayTree`, `palindromicTree`, `hashSuffixes`

### Miscellaneous
- `fastInput`, `fastDivider`, `hll`, etc.

The `test` directory contains simplified test versions of some snippets.

## Usage

Each file is self‑contained. Copy the desired snippet into your project or
include it directly when solving problems.
