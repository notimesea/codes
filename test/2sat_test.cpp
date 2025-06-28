#include <bits/stdc++.h>
using namespace std;
#include "2sat.hpp"
int main(){
    sat2 s(1);
    s.init();
    s.add(0,1);
    s.add(1,0);
    if(s.check()) return 1; // expect unsatisfiable
    return 0;
}
