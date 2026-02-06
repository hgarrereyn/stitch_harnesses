#include <cstdio>
extern "C" {
#include <BlackHole.h>
}
int main() {
    int v = BlackHole_Version();
    std::printf("BlackHole shim version: %d\n", v);
    return v==1 ? 0 : 1;
}
