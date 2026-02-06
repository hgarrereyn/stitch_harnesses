#include <stdio.h>
#include <classicube/ExtMath.h>

int main() {
    int a = -7;
    int b = Math_AbsI(a); // inline function
    float c = Math_SafeDiv(10.0f, 0.0f); // inline safe div
    printf("abs(%d) = %d, safeDiv=%.1f\n", a, b, c);
    return 0;
}
