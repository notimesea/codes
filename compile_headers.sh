#!/bin/bash
set -e
for header in *.hpp; do
  case "$header" in
    dominator_tree.hpp|implicit_treap.hpp|ntt.hpp)
      echo "Skipping $header (requires additional macros)"
      continue
      ;;
  esac
  echo "Testing $header"
  echo "#include \"$header\"\nint main(){}" > _tmp.cpp
  g++ -std=c++17 -c _tmp.cpp
  rm -f _tmp.o
done
rm -f _tmp.cpp
