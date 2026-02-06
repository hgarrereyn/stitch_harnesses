ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        build-essential zlib1g-dev && \
    rm -rf /var/lib/apt/lists/*

# Build static libraries for yarn and try and install headers
ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx
ENV PREFIX=/fuzz/install

RUN set -eux; \
    mkdir -p "$PREFIX"/lib "$PREFIX"/include; \
    cd /fuzz/src; \
    "$CC" -O2 -fPIC -c try.c -o try.o; \
    "$CC" -O2 -fPIC -c yarn.c -o yarn.o; \
    ar rcs libtry.a try.o; \
    ar rcs libyarn.a yarn.o; \
    install -m 0644 libtry.a libyarn.a "$PREFIX"/lib/; \
    install -m 0644 try.h yarn.h "$PREFIX"/include/
