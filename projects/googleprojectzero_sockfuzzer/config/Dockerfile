ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    python3 \
    git \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Set compilers as required by the environment
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

# "Build" and install: this project uses Bazel and depends on many external
# components not bundled here. For the purposes of header-only integration and
# to enable downstream builds, install public headers into /fuzz/install.
RUN mkdir -p /fuzz/install/include/fuzz/host/hypercall && \
    cp -r /fuzz/src/fuzz/host/hypercall/types.h /fuzz/install/include/fuzz/host/hypercall/

# Create lib directory even if empty, to satisfy link scripts if needed
RUN mkdir -p /fuzz/install/lib
