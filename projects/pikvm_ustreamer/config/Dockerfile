ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    pkg-config \
    libevent-dev \
    libjpeg-dev \
    libbsd-dev \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

WORKDIR /fuzz/src/src

RUN make clean || true
RUN make CC=$CC && make install PREFIX=/fuzz/install R_DESTDIR=

# Build a tiny static library exposing a simple API (base64)
RUN mkdir -p /fuzz/install/lib \
 && $CC -std=c17 -D_GNU_SOURCE -O2 -I/fuzz/src/src/libs -c /fuzz/src/src/libs/base64.c -o /tmp/base64.o \
 && ar rcs /fuzz/install/lib/libustreamer.a /tmp/base64.o

# Install headers for downstream builds
RUN mkdir -p /fuzz/install/include \
 && cp -v /fuzz/src/src/libs/*.h /fuzz/install/include/
