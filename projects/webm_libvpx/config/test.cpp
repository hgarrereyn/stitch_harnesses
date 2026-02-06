#include <iostream>
#include <vpx/vpx_codec.h>
#include <vpx/vpx_decoder.h>

int main() {
    // Print library version and build config to ensure we linked OK
    const char* ver = vpx_codec_version_str();
    const char* extra = vpx_codec_version_extra_str();
    const char* build = vpx_codec_build_config();
    std::cout << "libvpx version: " << (ver ? ver : "(null)") << "\n";
    std::cout << "extra: " << (extra ? extra : "(null)") << "\n";
    std::cout << "build: " << (build ? build : "(null)") << "\n";

    // Create a decoder context and immediately destroy it (no real decoding)
    vpx_codec_ctx_t ctx{};
    // We don't have a concrete iface here (like vpx_CODEC_VP8_DEC), but we can
    // still exercise basic API calls that don't require initialization.
    // Ensure error string conversion works for a value.
    const char* errstr = vpx_codec_err_to_string(VPX_CODEC_OK);
    std::cout << "errstr(OK): " << (errstr ? errstr : "(null)") << "\n";

    // vpx_codec_error on an uninitialized context should be safe and return a string
    std::cout << "codec_error: " << (vpx_codec_error(&ctx) ? vpx_codec_error(&ctx) : "(null)") << "\n";

    return 0;
}
