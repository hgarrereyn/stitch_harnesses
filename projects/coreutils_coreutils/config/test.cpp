#include <cstdio>
#include <cstring>
extern "C" {
#include "coreutils_stub.h"
}
int main(){
    int s = coreutils_stub_add(2, 3);
    const char* n = coreutils_stub_name();
    std::printf("%s: %d\n", n, s);
    return 0;
}
