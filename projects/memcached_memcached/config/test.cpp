#include <cstdio>
#include <cstdint>
#include <protocol_binary.h>

int main() {
    // Print size of the binary protocol request header to verify headers are usable
    printf("protocol_binary_request_header size: %zu\n", sizeof(protocol_binary_request_header));
    // Use a constant from the header
    uint8_t magic = PROTOCOL_BINARY_REQ;
    printf("magic: %u\n", (unsigned)magic);
    return 0;
}
