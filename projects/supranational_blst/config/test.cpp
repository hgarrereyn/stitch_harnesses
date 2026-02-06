#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "blst.h"

int main() {
    const char *msg = "hello blst";
    const size_t msg_len = strlen(msg);

    const uint8_t ikm[32] = {0};
    blst_scalar sk;
    blst_keygen(&sk, ikm, sizeof(ikm), NULL, 0);

    blst_p1 pk;
    blst_sk_to_pk_in_g1(&pk, &sk);
    blst_p1_affine pk_aff;
    blst_p1_to_affine(&pk_aff, &pk);

    blst_p2 hash;
    const char DST[] = "BLS_SIG_BLS12381G2_XMD:SHA-256_SSWU_RO_NUL_";
    blst_hash_to_g2(&hash, (const uint8_t*)msg, msg_len,
                    (const uint8_t*)DST, sizeof(DST)-1, NULL, 0);

    blst_p2 sig;
    blst_sign_pk_in_g1(&sig, &hash, &sk);
    blst_p2_affine sig_aff;
    blst_p2_to_affine(&sig_aff, &sig);

    BLST_ERROR err = blst_core_verify_pk_in_g1(&pk_aff, &sig_aff, 1,
                                               (const uint8_t*)msg, msg_len,
                                               (const uint8_t*)DST, sizeof(DST)-1,
                                               NULL, 0);

    if (err == BLST_SUCCESS) {
        printf("ok\n");
        return 0;
    } else {
        printf("verify failed: %d\n", (int)err);
        return 1;
    }
}
