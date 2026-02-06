ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and wolfSSL headers (for header-only codegen)
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      cmake ninja-build make pkg-config libwolfssl-dev && \
    rm -rf /var/lib/apt/lists/*

# Use the fuzzer compiler wrappers
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Configure, build, and install a static wolfMQTT without TLS (no external deps)
RUN mkdir -p build && cd build && \
    cmake -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=OFF \
      -DWOLFMQTT_TLS=no \
      -DWOLFMQTT_EXAMPLES=no \
      .. && \
    ninja -j"$(nproc)" && \
    ninja install

# Verify install
RUN test -f /fuzz/install/lib/libwolfmqtt.a && test -d /fuzz/install/include/wolfmqtt
