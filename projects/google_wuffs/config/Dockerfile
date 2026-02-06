ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install step: no external deps required. Prepare install prefix and copy the single-file library.
RUN set -eux; \
    mkdir -p /fuzz/install/include; \
    cp /fuzz/src/release/c/wuffs-v0.3.c /fuzz/install/include/

# Environment: compilers are provided by the base image. No build is needed as Wuffs ships as a single-file C library.
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install
