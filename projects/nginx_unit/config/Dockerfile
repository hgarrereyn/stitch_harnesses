ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies (ar, pkg-config)
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends binutils pkg-config && \
    rm -rf /var/lib/apt/lists/*

# Build and install libunit (static) to /fuzz/install
WORKDIR /fuzz/src

# Use the fuzzer compiler wrappers
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

# Configure with a fixed prefix and disable optional deps to keep build small
RUN ./configure --prefix=/fuzz/install --no-regex && \
    make -j"$(nproc)" libunit-install
