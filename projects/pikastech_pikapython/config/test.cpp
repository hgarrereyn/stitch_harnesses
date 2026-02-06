#include <cstdio>
extern "C" {
#include "dataString.h"
}

int main() {
    char buf[256];
    buf[0] = '\0';
    strAppend(buf, (char*)"Hello ");
    strAppend(buf, (char*)"PikaPython");
    size_t n = strGetSize(buf);
    std::printf("Built core string utils OK: %s (len=%zu)\n", buf, n);
    return 0;
}
