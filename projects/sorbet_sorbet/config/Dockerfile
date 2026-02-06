ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra dependencies needed for building the version library
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

# Build a tiny static library exposing Sorbet's version API and install headers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cd /fuzz/src && \
    "$CC" -O2 -fPIC -I/fuzz/src -c sorbet_version/sorbet_version.c -o /tmp/sorbet_version.o && \
    ar rcs /fuzz/install/lib/libsorbet_version.a /tmp/sorbet_version.o && \
    mkdir -p /fuzz/install/include/sorbet_version && \
    cp /fuzz/src/sorbet_version/sorbet_version.h /fuzz/install/include/sorbet_version/
