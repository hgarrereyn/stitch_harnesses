ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    libboost-dev \
    zlib1g-dev \
    protobuf-compiler \
    libprotobuf-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, install muduo
WORKDIR /fuzz/src

# Configure with cmake using the provided compilers and install prefix
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DMUDUO_BUILD_EXAMPLES=OFF \
    -DBUILD_SHARED_LIBS=OFF

RUN cmake --build build --target install
