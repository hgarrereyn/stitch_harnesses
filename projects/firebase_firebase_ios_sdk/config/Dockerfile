ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies (ensure cmake/ninja present) and Python venv
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    cmake ninja-build make \
    python3 python3-venv git ca-certificates pkg-config findutils \
 && rm -rf /var/lib/apt/lists/*

# Set compilers to fuzzer wrappers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz
RUN mkdir -p build install
WORKDIR /fuzz/build

# Configure: disable tests and ObjC layers to reduce deps
RUN cmake -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX=/fuzz/install \
  -DFIREBASE_IOS_BUILD_TESTS=OFF \
  -DFIRESTORE_INCLUDE_OBJC=OFF \
  /fuzz/src

# Build just the C++ core library and its deps
RUN ninja firestore_core

# "Install": copy headers and all static libs into the install prefix
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp -r /fuzz/src/Firestore/core/include/* /fuzz/install/include/ \
 && find /fuzz/build -name "*.a" -exec cp {} /fuzz/install/lib/ \;
