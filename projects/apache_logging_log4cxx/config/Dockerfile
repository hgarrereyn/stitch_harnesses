ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    pkg-config \
    libapr1-dev \
    libaprutil1-dev \
    libexpat1-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure and build log4cxx
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

RUN cmake -S . -B /tmp/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=${CC} \
    -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTING=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_SITE=OFF \
    -DBUILD_FUZZERS=OFF \
    -DLOG4CXX_WITH_PKG_CONFIG=ON \
 && cmake --build /tmp/build --target install -j$(nproc)
