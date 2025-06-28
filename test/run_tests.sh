#!/bin/bash
set -e
CXX=${CXX:-g++}
$CXX -std=c++11 test/2sat_test.cpp -o test/2sat_test
./test/2sat_test
$CXX -std=c++11 test/Bitset_test.cpp -o test/Bitset_test
./test/Bitset_test
