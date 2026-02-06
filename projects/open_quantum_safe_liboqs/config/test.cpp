#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <oqs/kem.h>

int main() {
    const char *alg = OQS_KEM_alg_ml_kem_512;
    OQS_KEM *kem = OQS_KEM_new(alg);
    if (!kem) {
        printf("Failed to init KEM %s\n", alg);
        return 0;
    }

    uint8_t *pk = (uint8_t *)malloc(kem->length_public_key);
    uint8_t *sk = (uint8_t *)malloc(kem->length_secret_key);
    uint8_t *ct = (uint8_t *)malloc(kem->length_ciphertext);
    uint8_t *ss_enc = (uint8_t *)malloc(kem->length_shared_secret);
    uint8_t *ss_dec = (uint8_t *)malloc(kem->length_shared_secret);

    if (!pk || !sk || !ct || !ss_enc || !ss_dec) {
        printf("Allocation failed\n");
        OQS_KEM_free(kem);
        free(pk); free(sk); free(ct); free(ss_enc); free(ss_dec);
        return 0;
    }

    if (OQS_KEM_keypair(kem, pk, sk) != OQS_SUCCESS) {
        printf("keypair failed\n");
    } else if (OQS_KEM_encaps(kem, ct, ss_enc, pk) != OQS_SUCCESS) {
        printf("encaps failed\n");
    } else if (OQS_KEM_decaps(kem, ss_dec, ct, sk) != OQS_SUCCESS) {
        printf("decaps failed\n");
    } else {
        bool ok = std::memcmp(ss_enc, ss_dec, kem->length_shared_secret) == 0;
        printf("liboqs: %s; pk=%zu sk=%zu ct=%zu ss=%zu; match=%s\n",
               alg,
               (size_t)kem->length_public_key,
               (size_t)kem->length_secret_key,
               (size_t)kem->length_ciphertext,
               (size_t)kem->length_shared_secret,
               ok ? "yes" : "no");
    }

    OQS_KEM_free(kem);
    free(pk); free(sk); free(ct); free(ss_enc); free(ss_dec);
    return 0;
}
