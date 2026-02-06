#include <cstdio>
#include "common.h"
extern "C" int starship_add(int a, int b);
int main(){
    int a = 7, b = 5;
    int c = starship_add(a,b);
    // use some typedefs from the project header to ensure it compiles
    s32 x = c; u8 y = (u8)(c);
    std::printf("starship_add(%d,%d)=%d; x=%d y=%u\n", a,b,c, x, y);
    return 0;
}
