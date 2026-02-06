ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build libnghttp2 (C library) statically using CMake

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    pkg-config \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Configure and build only the library, static-only, no docs/apps/examples
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=${CC} \
    -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DENABLE_LIB_ONLY=ON \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_STATIC_LIBS=ON \
    -DENABLE_DOC=OFF \
    -DENABLE_EXAMPLES=OFF \
    -DENABLE_HPACK_TOOLS=OFF \
    -DENABLE_APP=OFF \
 && cmake --build build --target install
