#include <cstdio>
#include <cstdint>
#include <vector>
#include <string>
#include <woff2/encode.h>
#include <woff2/decode.h>
#include <woff2/output.h>

int main() {
    // Dummy data that is not a valid font, just to exercise the API.
    const uint8_t dummy[1] = {0};

    // Encoder: ask for a max compressed size bound.
    size_t enc_bound = woff2::MaxWOFF2CompressedSize(dummy, sizeof(dummy));

    // Decoder: ask for final size; expected to be 0 for invalid input.
    size_t dec_size = woff2::ComputeWOFF2FinalSize(dummy, sizeof(dummy));

    // Also exercise WOFF2Out implementation
    std::string out_buf;
    woff2::WOFF2StringOut out(&out_buf);
    const char* msg = "hello";
    out.Write(msg, 5);

    std::printf("enc_bound=%zu dec_size=%zu out_size=%zu\n", enc_bound, dec_size, out.Size());
    return 0;
}
