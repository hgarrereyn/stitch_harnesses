ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tooling
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates build-essential \
 && rm -rf /var/lib/apt/lists/*

# Build a minimal static library from the Bosch BMA drivers, compiled as C++
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cd /fuzz/src/src && \
    $CXX -x c++ -O2 -fPIC -I/fuzz/src/src -c bma4.c -o /tmp/bma4.o && \
    $CXX -x c++ -O2 -fPIC -I/fuzz/src/src -c bma423.c -o /tmp/bma423.o && \
    ar rcs /fuzz/install/lib/libwatchy_bma.a /tmp/bma4.o /tmp/bma423.o && \
    install -m 0644 bma4_defs.h /fuzz/install/include/ && \
    install -m 0644 bma4.h /fuzz/install/include/ && \
    install -m 0644 bma423.h /fuzz/install/include/ && \
    install -m 0644 bma.h /fuzz/install/include/
