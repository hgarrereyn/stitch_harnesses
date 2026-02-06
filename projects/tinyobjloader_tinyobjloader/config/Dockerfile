ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      build-essential cmake ninja-build \
    && rm -rf /var/lib/apt/lists/*

# Configure and build tinyobjloader as a static library
WORKDIR /fuzz/src

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

RUN cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DTINYOBJLOADER_WITH_PYTHON=OFF \
    -DTINYOBJLOADER_BUILD_TEST_LOADER=OFF \
    -DTINYOBJLOADER_BUILD_OBJ_STICHER=OFF

RUN cmake --build build --target install -j$(nproc)
