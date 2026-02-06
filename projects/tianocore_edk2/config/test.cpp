#include <cstdio>
#include <cstdint>
#include <cstring>
extern "C" {
#include <Crc32.h>
}

int main() {
    const char* msg = "hello edk2";
    UINT32 crc = 0;
    EFI_STATUS st = CalculateCrc32((UINT8*)msg, (UINTN)std::strlen(msg), &crc);
    std::printf("status=%u crc=0x%08x\n", (unsigned)st, (unsigned)crc);
    return 0;
}
