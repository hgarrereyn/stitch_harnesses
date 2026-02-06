#include <rnp/rnp.h>
#include <cstdio>
#include <cstdlib>

int main() {
    rnp_ffi_t ffi = nullptr;
    // Create FFI with default key store formats
    rnp_result_t res = rnp_ffi_create(&ffi, RNP_KEYSTORE_GPG, RNP_KEYSTORE_GPG);
    if (res != 0 || !ffi) {
        std::printf("Failed to create FFI: %u\n", res);
        return 1;
    }

    const char* be = rnp_backend_string();
    const char* ver = rnp_backend_version();
    std::printf("rnp backend: %s, version: %s\n", be ? be : "?", ver ? ver : "?");

    // Just create/destroy an empty input/output to touch some API
    rnp_input_t in = nullptr;
    rnp_output_t out = nullptr;
    if (rnp_input_from_memory(&in, (const uint8_t*)"hello", 5, false) == 0 &&
        rnp_output_to_null(&out) == 0) {
        rnp_output_pipe(in, out);
    }
    if (in) rnp_input_destroy(in);
    if (out) rnp_output_destroy(out);

    rnp_ffi_destroy(ffi);
    return 0;
}
