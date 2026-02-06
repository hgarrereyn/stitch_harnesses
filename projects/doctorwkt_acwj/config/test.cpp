#include <cstdio>
#define class c_class
extern "C" {
#include "/fuzz/install/include/acwj/defs.h"
#include "/fuzz/install/include/acwj/decl.h"
}
#undef class

int main() {
    int l1 = genlabel();
    int l2 = genlabel();
    std::printf("Labels: %d %d\n", l1, l2);
    return 0;
}
