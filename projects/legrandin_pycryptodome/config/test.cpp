#include <cstdio>
#include <cstddef>
#include <cstdint>

extern "C" {
    typedef struct t_hash_state hash_state;
    int MD5_init(hash_state **mdState);
    int MD5_update(hash_state *hs, const unsigned char *buf, size_t len);
    int MD5_digest(const hash_state *mdState, unsigned char digest[16]);
    int MD5_destroy(hash_state *mdState);
}

int main() {
    hash_state *hs = nullptr;
    if (MD5_init(&hs) != 0) return 1;
    const char *msg = "hello world";
    MD5_update(hs, reinterpret_cast<const unsigned char*>(msg), 11);
    unsigned char out[16];
    MD5_digest(hs, out);
    MD5_destroy(hs);

    // Print first 4 bytes as hex to confirm it ran
    for (int i = 0; i < 4; i++) {
        std::printf("%02x", out[i]);
    }
    std::printf("\n");
    return 0;
}
