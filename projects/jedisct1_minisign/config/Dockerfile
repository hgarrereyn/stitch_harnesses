ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies: build tools, cmake, pkg-config, and libsodium
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        build-essential cmake pkg-config libsodium-dev ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Build and install minisign
WORKDIR /fuzz/src

# Configure with the fuzzing compilers and install prefix
RUN mkdir -p build && cd build && \
    cmake -DCMAKE_C_COMPILER=stitch_libafl_cc \
          -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
          -DCMAKE_BUILD_TYPE=RelWithDebInfo \
          -DCMAKE_INSTALL_PREFIX=/fuzz/install \
          .. && \
    make -j$(nproc) && \
    make install

# Install headers for fuzzing (not provided by upstream install)
RUN mkdir -p /fuzz/install/include && \
    cp -v src/*.h /fuzz/install/include/ && \
    printf "#ifndef MINISIGN_DEPS_H\n#define MINISIGN_DEPS_H 1\n#include <sodium.h>\n#endif\n" > /fuzz/install/include/minisign_deps.h
