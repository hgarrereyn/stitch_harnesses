ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal toolchain
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Manually install a minimal static library exposing a stable API: Weave/Support/Base64
RUN set -eux; \
    install -d /fuzz/install/include/Weave/Support /fuzz/install/lib; \
    cp src/lib/support/Base64.h /fuzz/install/include/Weave/Support/; \
    "$CXX" -c -O2 -fPIC -Isrc/lib/support -o /tmp/Base64.o src/lib/support/Base64.cpp; \
    ar rcs /fuzz/install/lib/libWeave.a /tmp/Base64.o; \
    ranlib /fuzz/install/lib/libWeave.a; \
    rm -f /tmp/Base64.o
