#include <cstdio>
#include <detours_compat.h>
int main(){
    std::printf("Detours version: 0x%x\n", DETOURS_VERSION);
    return 0;
}
