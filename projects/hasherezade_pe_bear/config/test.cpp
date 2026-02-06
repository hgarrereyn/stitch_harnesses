#include <capstone/capstone.h>
#include <cstdio>
int main() {
    int major = 0, minor = 0;
    unsigned int ver = cs_version(&major, &minor);
    std::printf("Capstone version: %u (%d.%d)\n", ver, major, minor);
    return 0;
}
