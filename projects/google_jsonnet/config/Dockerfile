ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install deps for building
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    pkg-config \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, install jsonnet
WORKDIR /fuzz/src

RUN cmake -S . -B /fuzz/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_TESTS=OFF \
    -DBUILD_JSONNET=ON \
    -DBUILD_JSONNETFMT=OFF \
    -DBUILD_STATIC_LIBS=ON \
    -DBUILD_SHARED_BINARIES=OFF

RUN cmake --build /fuzz/build --target install -- -v
