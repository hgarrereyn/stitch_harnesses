ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal build: build a static lib from a subset that doesn't pull heavy GTK deps
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    pkg-config \
    libglib2.0-dev \
    make \
    binutils \
    && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src

# Build a static library containing string utils
RUN mkdir -p build && \
    "$CC" -O2 -fPIC -Isrc -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -c src/fsearch_string_utils.c -o build/fsearch_string_utils.o && \
    ar -rcs build/libfsearch.a build/fsearch_string_utils.o && \
    mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cp build/libfsearch.a /fuzz/install/lib/ && \
    cp src/fsearch_string_utils.h /fuzz/install/include/
