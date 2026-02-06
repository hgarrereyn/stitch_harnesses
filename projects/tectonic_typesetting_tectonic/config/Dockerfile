ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools needed to build a static library (ar) and handle copying
RUN apt-get update && apt-get install -y --no-install-recommends binutils ca-certificates && rm -rf /var/lib/apt/lists/*

# Build and install the C bridge core static library and headers
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

# Compile the support C into a static library and install headers
RUN mkdir -p /tmp/build && \
    cd /fuzz/src/crates/bridge_core/support && \
    ${CC} -O2 -fno-omit-frame-pointer -c support.c -o /tmp/build/support.o -I . && \
    ar rcs /tmp/build/libtectonic_bridge_core.a /tmp/build/support.o && \
    mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp tectonic_bridge_core.h tectonic_bridge_core_generated.h /fuzz/install/include/ && \
    cp /tmp/build/libtectonic_bridge_core.a /fuzz/install/lib/
