#include <cstdio>
#include <cstdint>
#include <cstring>
extern "C" size_t ecdf_bitlen_from_tls_id(uint16_t);
#include "fuzz_ec.h"

int main() {
    uint16_t tlsid = 23; // secp256r1
    size_t bits = ecdf_bitlen_from_tls_id(tlsid);
    if (bits == 0) return 1;
    fuzzec_input_t in{};
    in.tls_id = tlsid;
    in.groupBitLen = bits;
    std::printf("Curve %u has %zu bits\n", tlsid, bits);
    return 0;
}
