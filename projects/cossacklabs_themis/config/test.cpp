#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
extern "C" {
#include <themis/secure_cell.h>
#include <themis/themis_error.h>
}

int main() {
    const uint8_t passphrase[] = "test-passphrase";
    const uint8_t context[] = "ctx";
    const uint8_t message[] = "hello themis";

    size_t enc_len = 0;
    themis_status_t res = themis_secure_cell_encrypt_seal_with_passphrase(
        passphrase, sizeof(passphrase)-1,
        context, sizeof(context)-1,
        message, sizeof(message)-1,
        nullptr, &enc_len);
    if (res != THEMIS_BUFFER_TOO_SMALL || enc_len == 0) {
        std::printf("unexpected status %d for length query\n", (int)res);
        return 1;
    }
    std::vector<uint8_t> enc(enc_len);
    res = themis_secure_cell_encrypt_seal_with_passphrase(
        passphrase, sizeof(passphrase)-1,
        context, sizeof(context)-1,
        message, sizeof(message)-1,
        enc.data(), &enc_len);
    if (res != THEMIS_SUCCESS) {
        std::printf("encrypt failed: %d\n", (int)res);
        return 1;
    }

    size_t dec_len = 0;
    res = themis_secure_cell_decrypt_seal_with_passphrase(
        passphrase, sizeof(passphrase)-1,
        context, sizeof(context)-1,
        enc.data(), enc_len,
        nullptr, &dec_len);
    if (res != THEMIS_BUFFER_TOO_SMALL || dec_len != sizeof(message)-1) {
        std::printf("unexpected dec length status %d, len %zu\n", (int)res, dec_len);
        return 1;
    }
    std::vector<uint8_t> dec(dec_len);
    res = themis_secure_cell_decrypt_seal_with_passphrase(
        passphrase, sizeof(passphrase)-1,
        context, sizeof(context)-1,
        enc.data(), enc_len,
        dec.data(), &dec_len);
    if (res != THEMIS_SUCCESS) {
        std::printf("decrypt failed: %d\n", (int)res);
        return 1;
    }

    std::string out(reinterpret_cast<char*>(dec.data()), dec_len);
    std::printf("Decrypted: %s\n", out.c_str());
    return 0;
}
