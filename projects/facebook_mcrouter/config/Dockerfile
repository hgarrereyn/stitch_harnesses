ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a minimal static library from mcrouter's fbi hashing code (no heavy deps)
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Build and install a static library and headers into /fuzz/install
RUN mkdir -p /fuzz/install/include/mcrouter/lib/fbi /fuzz/install/lib \
 && "$CC" -O2 -I. -I./mcrouter/lib/fbi -c mcrouter/lib/fbi/hash.c -o /tmp/hash.o \
 && ar rcs /fuzz/install/lib/libmcrouter_fbi.a /tmp/hash.o \
 && cp mcrouter/lib/fbi/hash.h mcrouter/lib/fbi/decls.h /fuzz/install/include/mcrouter/lib/fbi/
