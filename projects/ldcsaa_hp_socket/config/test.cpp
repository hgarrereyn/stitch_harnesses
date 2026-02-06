#include <iostream>
#include <vector>
#include <cstring>
#include <hpsocket/HPSocket.h>

int main() {
    const char* msg = "hello hp-socket";
    const BYTE* src = reinterpret_cast<const BYTE*>(msg);
    DWORD src_len = static_cast<DWORD>(std::strlen(msg));

    BYTE out[256];
    DWORD out_len = sizeof(out);

    int r = SYS_Base64Encode(src, src_len, out, out_len);
    if (r != NO_ERROR) {
        std::cout << "Base64Encode failed: " << r << std::endl;
        return 1;
    }

    std::cout << "Encoded length: " << out_len << " data: ";
    std::cout.write(reinterpret_cast<const char*>(out), out_len);
    std::cout << std::endl;

    return 0;
}
