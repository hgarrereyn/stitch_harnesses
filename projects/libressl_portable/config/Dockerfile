ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies for preparing and building from git checkout
RUN apt-get update && apt-get install -y --no-install-recommends \
    autoconf \
    automake \
    libtool \
    pkg-config \
    cmake \
    ninja-build \
    make \
    perl \
    ca-certificates \
  && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Prepare source tree (required from git checkout), then build with CMake
RUN bash ./autogen.sh \
  && mkdir -p build && cd build \
  && CC=stitch_libafl_cc CXX=stitch_libafl_cxx \
     cmake -G Ninja .. \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/fuzz/install \
        -DBUILD_SHARED_LIBS=OFF \
        -DLIBRESSL_APPS=OFF \
        -DLIBRESSL_TESTS=OFF \
        -DENABLE_ASM=ON \
  && ninja -j$(nproc) \
  && ninja install
