ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies: build tools and hiredis for redis-plus-plus
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        cmake \
        ninja-build \
        make \
        libhiredis-dev \
        ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, and install redis-plus-plus (static lib only)
WORKDIR /fuzz/src

RUN cmake -S . -B build \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DREDIS_PLUS_PLUS_BUILD_TEST=OFF \
    -DREDIS_PLUS_PLUS_BUILD_SHARED=OFF \
    -DREDIS_PLUS_PLUS_BUILD_STATIC=ON \
    -DREDIS_PLUS_PLUS_USE_TLS=OFF \
    -GNinja && \
    ninja -C build && \
    ninja -C build install
