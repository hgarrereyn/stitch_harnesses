ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools (cmake and ninja) if not present
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
    make \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Configure and build static library only
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_STATIC_LIBS=ON \
    -DBUILD_OBJECT_LIBS=OFF \
    -DJSONCPP_WITH_TESTS=OFF \
    -DJSONCPP_WITH_EXAMPLE=OFF

RUN cmake --build build --target install --config Release
