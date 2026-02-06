ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    make \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Build with fuzzing compiler and install to /fuzz/install
RUN make -j"$(nproc)" CC=gf_libafl_cc && \
    make install PREFIX=/fuzz/install CC=gf_libafl_cc

# Sanity check
RUN test -f /fuzz/install/lib/quickjs/libquickjs.a && \
    test -f /fuzz/install/include/quickjs/quickjs.h