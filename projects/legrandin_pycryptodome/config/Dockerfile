ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install any dependencies (none required beyond base tools)
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build a minimal static library exposing MD5 functions
ENV CC=stitch_libafl_cc

# Create install dirs
RUN mkdir -p /fuzz/install/include /fuzz/install/lib /fuzz/build

# Compile and install
WORKDIR /fuzz/src/src
RUN $CC -c MD5.c -O2 -g -I. \
    -DHAVE_STDINT_H -DHAVE_POSIX_MEMALIGN -DPYCRYPTO_LITTLE_ENDIAN -DHAVE_X86INTRIN_H -DUSE_SSE2 -DHAVE_UINT128 \
    -o /fuzz/build/MD5.o \
 && ar rcs /fuzz/install/lib/libpycryptodome.a /fuzz/build/MD5.o \
 && cp common.h endianess.h errors.h /fuzz/install/include/

WORKDIR /
