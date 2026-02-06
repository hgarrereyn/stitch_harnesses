ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal deps to build a tiny static lib from libsolutil (UTF8 only)
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

# Build a small, self-contained static library from libsolutil (UTF8)
WORKDIR /fuzz/src
RUN mkdir -p /fuzz/install/include/libsolutil /fuzz/install/lib \
 && $CXX -O2 -fPIC -std=c++17 -I/fuzz/src -c libsolutil/UTF8.cpp -o /tmp/UTF8.o \
 && ar rcs /fuzz/install/lib/libsolutil.a /tmp/UTF8.o \
 && cp libsolutil/UTF8.h /fuzz/install/include/libsolutil/
