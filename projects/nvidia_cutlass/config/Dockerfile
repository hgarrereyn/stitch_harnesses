ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# CUTLASS is a header-only library. We just need to install headers into /fuzz/install/include
# No CUDA toolkit is required to compile simple host code that only includes basic CUTLASS headers.

RUN set -eux; \
    mkdir -p /fuzz/install/include; \
    cp -r /fuzz/src/include/* /fuzz/install/include/

# Environment hints for any subsequent builds (not strictly required here)
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install
