ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools needed to build a static library (ar from binutils)
RUN apt-get update && apt-get install -y --no-install-recommends binutils && rm -rf /var/lib/apt/lists/*

# Set compilers as required
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

# Build a static liblinenoise.a and install headers
RUN mkdir -p /fuzz/build /fuzz/install/include /fuzz/install/lib && \
    cd /fuzz/build && \
    "$CC" -O2 -fPIC -c /fuzz/src/linenoise.c -o linenoise.o && \
    ar rcs liblinenoise.a linenoise.o && \
    install -m 0644 /fuzz/src/linenoise.h /fuzz/install/include/ && \
    install -m 0644 liblinenoise.a /fuzz/install/lib/
