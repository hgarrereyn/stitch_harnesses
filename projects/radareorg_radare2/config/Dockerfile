ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    python3-pip \
    pkg-config \
    git \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Install a recent meson (>=0.63)
RUN pip3 install --no-cache-dir 'meson>=0.63'

# Use the fuzzer compiler wrappers
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Configure (static libs where possible) and install to /fuzz/install
RUN meson setup build \
    -Ddefault_library=static \
    -Dcli=disabled \
    -Denable_tests=false \
    -Denable_r2r=false \
    -Denable_libfuzzer=false \
    -Dwant_qjs=false \
    -Duse_ssl=false \
    -Duse_libuv=false \
    --prefix=/fuzz/install \
    --libdir=lib \
    --includedir=include

RUN ninja -C build
RUN meson install -C build
