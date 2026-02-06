ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal build: build static lib from tiv_lib.cpp and install headers
RUN apt-get update && apt-get install -y --no-install-recommends binutils ca-certificates && rm -rf /var/lib/apt/lists/*

# Build and install static library
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
    && cd /fuzz/src/src \
    && stitch_libafl_cxx -O2 -fPIC -c tiv_lib.cpp -o tiv_lib.o \
    && ar rcs libtiv.a tiv_lib.o \
    && cp libtiv.a /fuzz/install/lib/ \
    && cp tiv_lib.h /fuzz/install/include/
