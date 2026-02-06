#include <cstdio>
#include <cstring>
extern "C" {
#include <zlib.h>
}

int main() {
    const unsigned char data[] = "Hello, ReactOS zlibhost!";
    uLong crc = crc32(0L, Z_NULL, 0);
    crc = crc32(crc, data, (uInt)strlen((const char*)data));

    const char* ver = zlibVersion();
    // Print something deterministic so the program can be validated
    std::printf("zlib version: %s, crc32: %lu\n", ver, (unsigned long)crc);
    return 0;
}
