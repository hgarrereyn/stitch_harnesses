ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies (cmake, ninja) and minimal runtime deps
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Configure, build and install libcoap (static, no DTLS, no docs/examples/tests)
WORKDIR /fuzz/src
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DENABLE_DTLS=OFF \
    -DENABLE_EXAMPLES=OFF \
    -DENABLE_TESTS=OFF \
    -DENABLE_DOCS=OFF
RUN cmake --build build --target install -j
