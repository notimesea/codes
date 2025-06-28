#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
#include "../bitset.hpp"
int main(){
    Bitset b(64);
    b.set(5);
    if(!b.test(5)) return 1;
    b.reset(5);
    if(b.test(5)) return 1;
    return 0;
}
