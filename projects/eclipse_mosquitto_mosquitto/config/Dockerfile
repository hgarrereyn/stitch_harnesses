ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build pkg-config libssl-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure with CMake to build libraries only
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DWITH_CLIENTS=OFF \
    -DWITH_BROKER=OFF \
    -DWITH_APPS=OFF \
    -DWITH_PLUGINS=OFF \
    -DDOCUMENTATION=OFF \
    -DWITH_STATIC_LIBRARIES=ON \
    -DWITH_PIC=ON \
    -DWITH_SRV=OFF \
    -DWITH_WEBSOCKETS=OFF

# Build and install
RUN cmake --build build --target install
