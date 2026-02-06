#include <iostream>
#include <cstring>
extern "C" {
#include <tomcrypt.h>
}

int main() {
    register_all_hashes();
    register_all_ciphers();
    register_all_prngs();

    const char* msg = "hello";
    unsigned char out[32];
    unsigned long outlen = sizeof(out);

    int idx = find_hash("sha256");
    if (idx == -1) {
        std::cerr << "sha256 not found" << std::endl;
        return 1;
    }

    int err = hash_memory(idx, reinterpret_cast<const unsigned char*>(msg), std::strlen(msg), out, &outlen);
    if (err != CRYPT_OK) {
        std::cerr << "hash_memory failed: " << error_to_string(err) << std::endl;
        return 1;
    }

    unsigned int acc = 0;
    for (unsigned long i = 0; i < outlen; ++i) acc += out[i];
    std::cout << "sha256(hello) length=" << outlen << ", checksum=" << acc << std::endl;
    return 0;
}
