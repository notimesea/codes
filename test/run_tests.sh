#!/bin/bash
set -e
CXX=${CXX:-g++}
CXXFLAGS=${CXXFLAGS:--std=c++17 -O2}
$CXX $CXXFLAGS test/2sat_test.cpp -o test/2sat_test
./test/2sat_test
$CXX $CXXFLAGS test/Bitset_test.cpp -o test/Bitset_test
./test/Bitset_test
