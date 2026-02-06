ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and minimal deps
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
    make \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure and build static libhv
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src

# Configure with CMake: static only, no examples/tests
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED=OFF \
    -DBUILD_STATIC=ON \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_UNITTEST=OFF \
    -DWITH_PROTOCOL=OFF \
    -DWITH_NGHTTP2=OFF \
    -DWITH_OPENSSL=OFF \
    -DWITH_GNUTLS=OFF \
    -DWITH_MBEDTLS=OFF \
    -DWITH_MQTT=OFF

RUN cmake --build build --target install -- -v
