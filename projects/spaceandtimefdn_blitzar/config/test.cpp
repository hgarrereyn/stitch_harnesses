#include <cstdio>
#include <cstdint>
#include "cbindings/blitzar_api.h"

int main() {
    sxt_config cfg; 
    cfg.backend = SXT_CPU_BACKEND; 
    cfg.num_precomputed_generators = 0; 
    if (sxt_init(&cfg) != 0) {
        return 1;
    }
    const uint64_t n = 3;
    const uint8_t nb = 1;
    uint8_t data[nb * n] = {1, 2, 3};
    sxt_sequence_descriptor desc{nb, n, data, 0};
    sxt_ristretto255_compressed out[1];
    sxt_curve25519_compute_pedersen_commitments(out, 1, &desc, 0);
    volatile unsigned sum = 0;
    const unsigned char* p = reinterpret_cast<const unsigned char*>(out);
    for (size_t i = 0; i < sizeof(out); ++i) sum += p[i];
    return sum == 0xFFFFFFFFu ? 1 : 0;
}
