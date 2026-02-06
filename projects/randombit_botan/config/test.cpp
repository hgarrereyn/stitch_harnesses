#include <botan/ffi.h>
#include <cstdio>
#include <cstring>

int main() {
    // Print version via C FFI
    const char* ver = botan_version_string();
    std::printf("Botan version: %s\n", ver);

    // Compute SHA-256 of a small message via C FFI
    botan_hash_t hash = nullptr;
    if(botan_hash_init(&hash, "SHA-256", 0) != 0) {
        std::printf("hash_init failed\n");
        return 1;
    }

    const char* msg = "hello botan";
    botan_hash_update(hash, reinterpret_cast<const uint8_t*>(msg), std::strlen(msg));

    size_t out_len = 0;
    botan_hash_output_length(hash, &out_len);
    uint8_t out[64] = {0};
    if(out_len > sizeof(out)) out_len = sizeof(out);

    botan_hash_final(hash, out);
    botan_hash_destroy(hash);

    unsigned sum = 0; for(size_t i = 0; i < out_len; ++i) sum += out[i];
    std::printf("digest size: %zu checksum: %u\n", out_len, sum);
    return 0;
}
