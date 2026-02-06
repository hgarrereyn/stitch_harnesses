#include "/fuzz/install/include/iso646.h"
int main(){
    bool a = true;
    bool b = false;
    bool c = a and b;
    int x = 1;
    int y = 2;
    int z = x bitor y; // 1 | 2 == 3
    return (c == false && z == 3) ? 0 : 1;
}
