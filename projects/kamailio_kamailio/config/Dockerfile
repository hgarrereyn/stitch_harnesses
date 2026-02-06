ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install a tiny static library from Kamailio core (bit operations)
# Compilers are provided by the base image as wrappers around clang-17
ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

RUN set -eux; \
    mkdir -p /fuzz/install/lib /fuzz/install/include; \
    # Compile standalone core sources that have no external deps
    ${CC} -fPIC -O2 -c /fuzz/src/src/core/bit_count.c -o /tmp/bit_count.o; \
    ${CC} -fPIC -O2 -c /fuzz/src/src/core/bit_scan.c -o /tmp/bit_scan.o; \
    ar rcs /fuzz/install/lib/libkamcorebits.a /tmp/bit_count.o /tmp/bit_scan.o; \
    cp /fuzz/src/src/core/bit_count.h /fuzz/install/include/; \
    cp /fuzz/src/src/core/bit_scan.h /fuzz/install/include/
