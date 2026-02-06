ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    nasm \
 && rm -rf /var/lib/apt/lists/*

# Use the fuzzer compiler wrappers
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Build and install static library and headers using Makefile
RUN make -j"$(nproc)" V=Yes \
 && make install-static PREFIX=/fuzz/install
