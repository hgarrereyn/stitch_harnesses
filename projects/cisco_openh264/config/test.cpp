#include <wels/codec_api.h>
#include <cstdio>

int main() {
    // Query version
    OpenH264Version ver{};
    WelsGetCodecVersionEx(&ver);
    std::printf("OpenH264 version: %d.%d.%d.%d\n", ver.uMajor, ver.uMinor, ver.uRevision, ver.uReserved);

    // Create and destroy encoder
    ISVCEncoder* enc = nullptr;
    if (WelsCreateSVCEncoder(&enc) == 0 && enc) {
        WelsDestroySVCEncoder(enc);
    } else {
        std::printf("Failed to create encoder\n");
    }

    // Create and destroy decoder
    ISVCDecoder* dec = nullptr;
    if (WelsCreateDecoder(&dec) == 0 && dec) {
        WelsDestroyDecoder(dec);
    } else {
        std::printf("Failed to create decoder\n");
    }

    return 0;
}
