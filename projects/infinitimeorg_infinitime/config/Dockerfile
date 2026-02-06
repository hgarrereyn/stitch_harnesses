ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools needed to build a static library
RUN apt-get update && apt-get install -y --no-install-recommends \
    binutils \
 && rm -rf /var/lib/apt/lists/*

# Build a minimal static library from the host-buildable component (RLE decoder)
# Use the provided fuzzing compiler wrappers
ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Compile the RLE decoder into a static library and install headers
RUN mkdir -p /fuzz/build && \
    "$CXX" -c -O2 -I/fuzz/src/src -o /fuzz/build/RleDecoder.o src/components/rle/RleDecoder.cpp && \
    mkdir -p /fuzz/install/lib /fuzz/install/include/InfiniTime/components/rle && \
    ar rcs /fuzz/install/lib/libinfinitime_rle.a /fuzz/build/RleDecoder.o && \
    cp src/components/rle/RleDecoder.h /fuzz/install/include/InfiniTime/components/rle/RleDecoder.h

# Nothing else to build/install
