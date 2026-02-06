ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    pkg-config \
    git \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    INSTALL_PREFIX=/fuzz/install

WORKDIR /fuzz/src

# Configure and build shared library with minimal features and vendored deps
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} \
    -DBTCPP_SHARED_LIBS=ON \
    -DBTCPP_BUILD_TOOLS=OFF \
    -DBTCPP_EXAMPLES=OFF \
    -DBUILD_TESTING=OFF \
    -DBTCPP_GROOT_INTERFACE=OFF \
    -DBTCPP_SQLITE_LOGGING=OFF \
    -DUSE_VENDORED_TINYXML2=ON \
    -DUSE_VENDORED_CPPZMQ=ON \
    -DUSE_VENDORED_FLATBUFFERS=ON \
    -DUSE_VENDORED_LEXY=ON \
    -DUSE_VENDORED_MINICORO=ON \
    -DUSE_VENDORED_MINITRACE=ON

RUN cmake --build build --parallel
RUN cmake --install build
