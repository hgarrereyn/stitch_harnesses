ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure and build libevent (static, no tests/samples, no SSL/mbedtls)
WORKDIR /fuzz/src
RUN mkdir -p build && cd build && \
    CC=gf_libafl_cc CXX=gf_libafl_cxx \
    cmake -G Ninja .. \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DEVENT__LIBRARY_TYPE=STATIC \
      -DEVENT__DISABLE_TESTS=ON \
      -DEVENT__DISABLE_REGRESS=ON \
      -DEVENT__DISABLE_SAMPLES=ON \
      -DEVENT__DISABLE_OPENSSL=ON \
      -DEVENT__DISABLE_MBEDTLS=ON \
      -DEVENT__DISABLE_BENCHMARK=ON \
      -DEVENT__DISABLE_DEBUG_MODE=ON \
    && ninja -v \
    && ninja install

ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig
