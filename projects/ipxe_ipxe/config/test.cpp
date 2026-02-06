#include <iostream>
#include <cstring>
extern "C" {
#include <ipxe/base64.h>
}

int main() {
    const char* msg = "hello ipxe";
    char enc[128] = {0};
    char dec[128] = {0};

    size_t need = base64_encoded_len(strlen(msg));
    size_t wrote = base64_encode(msg, strlen(msg), enc, sizeof(enc));
    int dec_len = base64_decode(enc, dec, sizeof(dec));

    std::cout << "need=" << need << ", wrote=" << wrote << ", dec_len=" << dec_len << "\n";
    std::cout << "enc=" << enc << "\n";
    std::cout << "dec=" << dec << "\n";

    return 0;
}
