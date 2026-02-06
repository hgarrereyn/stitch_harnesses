ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies, cmake, and git to fetch submodules
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    git \
    cmake \
    ninja-build \
    pkg-config \
    libssl-dev \
    zlib1g-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Fetch submodules (Connector/C lives in libmariadb)
WORKDIR /fuzz/src
RUN git submodule update --init --recursive --depth 1

# Configure and build MariaDB Connector/C only
RUN cmake -G Ninja -S /fuzz/src/libmariadb -B /fuzz/build \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DWITH_SSL=OPENSSL \
    -DWITH_EXTERNAL_ZLIB=ON \
    -DWITH_UNIT_TESTS=OFF \
    -DDISABLE_SHARED=ON

RUN cmake --build /fuzz/build --target install -j
