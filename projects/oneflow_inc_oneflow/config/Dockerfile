ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal install: header-only subset (oneflow/maybe)
# We avoid building the full project to keep the image small and fast for fuzzing.

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PREFIX=/fuzz/install

RUN set -eux; \
    mkdir -p "$PREFIX/include/oneflow/maybe"; \
    cp -v /fuzz/src/oneflow/maybe/*.h "$PREFIX/include/oneflow/maybe/";

# No library to build/link; the maybe API is header-only.
