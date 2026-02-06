#include <bits/stdc++.h>
using namespace std;
#include "geometry/lineIntersection.h"

int main() {
    Point<double> s1(0,0), e1(1,1);
    Point<double> s2(0,1), e2(1,0);
    auto res = lineInter(s1, e1, s2, e2);
    if (res.first == 1) {
        cout << res.second.x << "," << res.second.y << "\n";
    } else {
        cout << "no intersection" << "\n";
    }
    return 0;
}
