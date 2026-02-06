ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies and build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    pkg-config \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure and build static libcurl only
WORKDIR /fuzz/src

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

RUN cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_STATIC_LIBS=ON \
    -DBUILD_CURL_EXE=OFF \
    -DENABLE_ARES=OFF \
    -DCURL_ENABLE_SSL=OFF \
    -DCURL_USE_OPENSSL=OFF \
    -DCURL_USE_LIBPSL=OFF \
    -DCURL_USE_LIBSSH2=OFF \
    -DCURL_USE_BROTLI=OFF \
    -DCURL_ZLIB=OFF \
    -DCURL_ZSTD=OFF \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON && \
    cmake --build build --target install -j$(nproc)
