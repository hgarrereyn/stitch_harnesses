ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools (no heavy deps). We only install headers for now.
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    python3 \
 && rm -rf /var/lib/apt/lists/*

# Ensure the requested compilers are selected for any builds
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

# "Install" the public headers into /fuzz/install
RUN mkdir -p /fuzz/install/include && \
    cp -r /fuzz/src/include/* /fuzz/install/include/ && \
    mkdir -p /fuzz/install/modules && \
    cp -r /fuzz/src/modules/skcms /fuzz/install/modules/ && \
    mkdir -p /fuzz/install/lib
