ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a minimal static library from Core Lightning sources that are self-contained
# and do not require external submodules.

ENV DEBIAN_FRONTEND=noninteractive

# No extra packages required; build tools and clang wrappers are preinstalled.

# Setup compilers and install prefix
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx PREFIX=/fuzz/install

RUN mkdir -p /build/include && \
    echo "/* Minimal config for building standalone common components */\n#ifndef LIGHTNING_CONFIG_H\n#define LIGHTNING_CONFIG_H\n#endif" > /build/include/config.h && \
    mkdir -p ${PREFIX}/lib ${PREFIX}/include/common && \
    # Compile the standalone bech32 component
    ${CC} -fPIC -I/build/include -I/fuzz/src -c /fuzz/src/common/bech32.c -o /build/bech32.o && \
    # Create a static library
    ar rcs /build/libclnmini.a /build/bech32.o && \
    # Install library and headers
    cp /build/libclnmini.a ${PREFIX}/lib/ && \
    cp /build/include/config.h ${PREFIX}/include/ && \
    cp /fuzz/src/common/bech32.h ${PREFIX}/include/common/
