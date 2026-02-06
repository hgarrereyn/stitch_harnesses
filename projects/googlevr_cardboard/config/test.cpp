#include <cstdio>
#include <cardboard.h>
int main() {
    int count = CardboardQrCode_getDeviceParamsChangedCount();
    std::printf("Device params changed count: %d\n", count);
    return 0;
}
