ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build minimal static libdnsmasq.a exposing a tiny API based on project headers
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      build-essential ca-certificates && \
    rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Build and install
RUN set -eux; \
    install -d /fuzz/install/include /fuzz/install/lib /fuzz/build; \
    cd /fuzz/build; \
    printf '%s\n' '#include "../src/src/dnsmasq.h"' 'int dnsmasq_rr_mx(void){ return T_MX; }' > mini_api.c; \
    ${CC} -O2 -ffunction-sections -fdata-sections -I/fuzz/src/src -c mini_api.c -o mini_api.o; \
    ar rcs /fuzz/install/lib/libdnsmasq.a mini_api.o; \
    # Install a C++-friendly project header for codegen
    cp -a /fuzz/src/src/metrics.h /fuzz/install/include/
