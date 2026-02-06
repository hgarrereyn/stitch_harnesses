ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal dependencies for building dxflib
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
    make \
    findutils \
    && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Build only dxflib
WORKDIR /fuzz/build
RUN cmake -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    /fuzz/src/src/3rdparty/dxflib
RUN cmake --build . --target dxflib -j

# Install headers (no official install rules)
RUN mkdir -p /fuzz/install/include/dxflib /fuzz/install/lib && \
    cp -r /fuzz/src/src/3rdparty/dxflib/src/* /fuzz/install/include/dxflib/
