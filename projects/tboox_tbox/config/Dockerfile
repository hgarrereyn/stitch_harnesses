ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends pkg-config ca-certificates && rm -rf /var/lib/apt/lists/*

# Provide clang/clang++ shims that route to the fuzzing compiler wrappers
RUN mkdir -p /fuzz/wrappers && \
    printf '#!/bin/sh\nexec stitch_libafl_cc "$@"\n' > /fuzz/wrappers/clang && chmod +x /fuzz/wrappers/clang && \
    printf '#!/bin/sh\nexec stitch_libafl_cxx "$@"\n' > /fuzz/wrappers/clang++ && chmod +x /fuzz/wrappers/clang++
ENV PATH=/fuzz/wrappers:${PATH}

# Build and install tbox as a static library
WORKDIR /fuzz/src
RUN ./configure --prefix=/fuzz/install --kind=static --mode=release --toolchain=clang && \
    make -j"$(nproc)" && \
    make install
