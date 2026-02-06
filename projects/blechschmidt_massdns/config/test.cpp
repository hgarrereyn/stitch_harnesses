#include <cstdio>
#include "/fuzz/install/include/massdns/buffers.h"

int main() {
    buffer_t buf{};
    buf.data = nullptr;
    buf.len = 0;
    std::printf("ok\n");
    return 0;
}
