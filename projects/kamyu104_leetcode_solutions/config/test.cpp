#include <cstdio>
#include "leetcode.h"
int main(){
    int a = 2, b = 3;
    int c = kamyu_sum(a,b);
    // simple self-check
    if(c != 5){
        printf("Unexpected result: %d\n", c);
        return 1;
    }
    printf("kamyu_sum(%d,%d) = %d\n", a, b, c);
    return 0;
}
