#include <cstdio>
#include "hw.h"

int main() {
    const char* name = hw_name();
    int s = hw_sum(13, 29);
    std::printf("%s %d\n", name, s);
    return 0;
}
