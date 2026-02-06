#include <cstdio>
#include "volk.h"

int main() {
    VkResult r = volkInitialize();
    std::printf("VOLK_HEADER_VERSION=%d, volkInitialize=%d\n", VOLK_HEADER_VERSION, (int)r);
    return 0;
}
