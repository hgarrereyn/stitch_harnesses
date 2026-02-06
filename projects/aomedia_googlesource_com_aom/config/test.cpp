#include <iostream>
#include <aom/aom_decoder.h>
#include <aom/aomdx.h>
#include <aom/aom_codec.h>

int main() {
    aom_codec_ctx_t ctx;
    const aom_codec_iface_t *iface = aom_codec_av1_dx();
    if (!iface) {
        std::cout << "Failed to get AV1 decoder interface" << std::endl;
        return 1;
    }
    aom_codec_err_t res = aom_codec_dec_init(&ctx, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) {
        std::cout << "Decoder init failed: " << aom_codec_err_to_string(res) << std::endl;
        return 1;
    }
    // No data to decode; just destroy immediately.
    aom_codec_destroy(&ctx);
    std::cout << "libaom decoder initialized and destroyed successfully" << std::endl;
    return 0;
}
