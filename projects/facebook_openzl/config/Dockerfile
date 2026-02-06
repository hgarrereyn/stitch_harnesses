ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and system libs for zstd/lz4
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    build-essential \
    make \
    cmake \
    ninja-build \
    pkg-config \
    libzstd-dev \
    liblz4-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Build static library using Makefile, forcing system zstd/lz4 and skipping heavy deps
RUN make libopenzl.a \
    CC=stitch_libafl_cc CXX=stitch_libafl_cxx \
    BUILD_TYPE=OPT \
    SKIP_BUILDDEPS_CHECK=1 \
    LIBXGBOOST_A= LIBDMLC_A= \
    LIBZSTD_A=/usr/lib/x86_64-linux-gnu/libzstd.a \
    LIBLZ4_A=/usr/lib/x86_64-linux-gnu/liblz4.a

# Install headers and library
RUN mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cp -a include/openzl /fuzz/install/include/ && \
    cp libopenzl.a /fuzz/install/lib/
