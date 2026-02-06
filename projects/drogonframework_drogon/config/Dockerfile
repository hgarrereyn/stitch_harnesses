ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and runtime libs
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    git \
    cmake \
    ninja-build \
    pkg-config \
    libjsoncpp-dev \
    libssl-dev \
    zlib1g-dev \
    libc-ares-dev \
    uuid-dev \
    && rm -rf /var/lib/apt/lists/*

# Fetch submodules (trantor)
WORKDIR /fuzz/src
RUN git submodule update --init --recursive

# Configure, build, and install drogon
WORKDIR /fuzz/build
RUN cmake -G Ninja \
    -S /fuzz/src \
    -B /fuzz/build \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_CTL=OFF \
    -DBUILD_ORM=OFF \
    -DBUILD_BROTLI=OFF \
    -DBUILD_YAML_CONFIG=OFF \
    -DUSE_SUBMODULE=ON \
    -DBUILD_SHARED_LIBS=OFF \
    && ninja -j"$(nproc)" install
