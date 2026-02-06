ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    git \
    python3 \
 && rm -rf /var/lib/apt/lists/*

ENV PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/lib ${PREFIX}/include/cbindings /tmp/build

# Install public headers from the repo
WORKDIR /fuzz/src
RUN cp -r cbindings/*.h ${PREFIX}/include/cbindings/

# Build a minimal compatibility library exposing a subset of the C API used by tests
WORKDIR /tmp/build
RUN printf '%s\n' \
'#include <stdint.h>' \
'#include <stddef.h>' \
'#include "cbindings/blitzar_api.h"' \
'extern "C" {' \
'int sxt_init(const struct sxt_config* cfg) { (void)cfg; return 0; }' \
'void sxt_curve25519_compute_pedersen_commitments(struct sxt_ristretto255_compressed* commitments,' \
'                                                 uint32_t num_sequences,' \
'                                                 const struct sxt_sequence_descriptor* descriptors,' \
'                                                 uint64_t offset_generators) {' \
'  (void)commitments; (void)num_sequences; (void)descriptors; (void)offset_generators; }' \
'}' > stub.cpp

RUN stitch_libafl_cxx -fPIC -shared stub.cpp -I${PREFIX}/include -o ${PREFIX}/lib/libblitzar.so

