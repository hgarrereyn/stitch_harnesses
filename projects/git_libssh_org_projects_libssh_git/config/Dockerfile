ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies for building libssh statically with OpenSSL and zlib
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    pkg-config \
    ninja-build \
    libssl-dev \
    zlib1g-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure, build and install libssh
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src

RUN cmake -S . -B /tmp/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DWITH_GSSAPI=OFF \
    -DWITH_MBEDTLS=OFF \
    -DWITH_GCRYPT=OFF \
    -DWITH_EXAMPLES=OFF \
    && cmake --build /tmp/build --target install -j$(nproc)
