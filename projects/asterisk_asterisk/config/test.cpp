#include <cstdio>
#include <cstring>
extern "C" {
#include <asterisk/md5.h>
}

int main() {
    const char *msg = "hello";
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5Context ctx{};
    MD5Init(&ctx);
    MD5Update(&ctx, reinterpret_cast<const unsigned char*>(msg), (unsigned)std::strlen(msg));
    MD5Final(digest, &ctx);
    // Print digest as hex
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        std::printf("%02x", digest[i]);
    }
    std::printf("\n");
    return 0;
}
