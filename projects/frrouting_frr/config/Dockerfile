ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    python3 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Install headers (copy from source tree)
RUN mkdir -p /fuzz/install/include/lib && \
    find lib -maxdepth 1 -type f -name '*.h' -exec cp -v {} /fuzz/install/include/lib/ \; && \
    mkdir -p /fuzz/install/include/lib/assert && \
    cp -v lib/assert/assert.h /fuzz/install/include/lib/assert/ || true && \
    # provide generated headers placeholders
    printf "/* generated placeholder */\n#ifndef FRR_VERSION_H\n#define FRR_VERSION_H 1\n#define FRR_VERSION \"fuzz\"\n#endif\n" > /fuzz/install/include/lib/version.h && \
    printf "/* generated placeholder */\n#ifndef FRR_ROUTE_TYPES_H\n#define FRR_ROUTE_TYPES_H 1\n#endif\n" > /fuzz/install/include/lib/route_types.h

# Build a minimal static libfrr with a subset of sources sufficient for linking
RUN mkdir -p /fuzz/build && \
    stitch_libafl_cc -c -O2 -fPIC -I. -Ilib -o /fuzz/build/base64.o lib/base64.c && \
    ar rcs /fuzz/build/libfrr.a /fuzz/build/base64.o && \
    mkdir -p /fuzz/install/lib && \
    cp /fuzz/build/libfrr.a /fuzz/install/lib/
