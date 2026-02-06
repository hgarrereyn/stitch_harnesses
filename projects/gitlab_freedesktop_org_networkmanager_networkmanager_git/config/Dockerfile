ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build the small c-siphash library manually (no extra deps required)
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src

# Build and install static libcsiphash.a
RUN mkdir -p /fuzz/install/lib /fuzz/install/include && \
    $CC -std=c11 -O2 -c src/c-siphash/src/c-siphash.c -I src/c-stdaux/src -o /tmp/c-siphash.o && \
    ar rcs /fuzz/install/lib/libcsiphash.a /tmp/c-siphash.o && \
    cp src/c-siphash/src/c-siphash.h /fuzz/install/include/
