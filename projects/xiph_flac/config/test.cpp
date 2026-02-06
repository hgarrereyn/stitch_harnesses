#include <cstdio>
#include <cstdint>
// Provide definitions required when lib was built with FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION
extern "C" {
    int alloc_check_threshold = INT32_MAX;
    int alloc_check_counter = 0;
    int alloc_check_keep_failing = 0;
}
#include <FLAC/stream_decoder.h>

int main() {
    FLAC__StreamDecoder *dec = FLAC__stream_decoder_new();
    if (!dec) {
        std::printf("Failed to create decoder\n");
        return 1;
    }
    FLAC__bool md5check = FLAC__stream_decoder_get_md5_checking(dec);
    std::printf("MD5 checking default: %s\n", md5check ? "true" : "false");
    FLAC__stream_decoder_delete(dec);
    return 0;
}
