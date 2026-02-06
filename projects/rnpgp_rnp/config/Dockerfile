ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for rnpgp rnp (OpenSSL backend)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    pkg-config \
    ninja-build \
    cmake \
    make \
    libssl-dev \
    libjson-c-dev \
    zlib1g-dev \
    libbz2-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install rnp
WORKDIR /fuzz/src

# Use a separate build directory
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DCRYPTO_BACKEND=openssl \
    -DBUILD_TESTING=OFF \
    -DENABLE_DOC=Off \
    -DDOWNLOAD_GTEST=Off \
    -DSYSTEM_LIBSEXPP=OFF \
 && cmake --build build --target install --parallel
