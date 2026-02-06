#include <sodium.h>
#include <cstdio>
#include <cstring>

int main() {
    if (sodium_init() < 0) {
        return 1; // panic! the library couldn't be initialized
    }

    const char *msg = "hello, libsodium";
    unsigned char hash[crypto_hash_sha256_BYTES];
    crypto_hash_sha256_state st;

    if (crypto_hash_sha256_init(&st) != 0) return 2;
    crypto_hash_sha256_update(&st, reinterpret_cast<const unsigned char*>(msg), std::strlen(msg));
    crypto_hash_sha256_final(&st, hash);

    unsigned char key[crypto_secretbox_KEYBYTES];
    randombytes_buf(key, sizeof key);

    unsigned char nonce[crypto_secretbox_NONCEBYTES];
    randombytes_buf(nonce, sizeof nonce);

    const unsigned char plaintext[] = "Hi";
    unsigned char ciphertext[crypto_secretbox_MACBYTES + sizeof plaintext];

    if (crypto_secretbox_easy(ciphertext, plaintext, sizeof plaintext, nonce, key) != 0) return 3;

    printf("hash_first_byte=%u cipher_first_byte=%u\n", (unsigned)hash[0], (unsigned)ciphertext[0]);
    return 0;
}
