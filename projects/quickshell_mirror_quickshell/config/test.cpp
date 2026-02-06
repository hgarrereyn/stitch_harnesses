#include <cstdio>
#include <quickshell_stub.hpp>

int main() {
    int x = qs_add(2, 5);
    std::printf("qs_add(2,5)=%d\n", x);
    return x == 7 ? 0 : 1;
}
