ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and system deps
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
    make \
    pkg-config \
    zlib1g-dev \
    libpugixml-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure and build assimp statically
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src

RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=${CC} \
    -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DASSIMP_BUILD_TESTS=OFF \
    -DASSIMP_BUILD_ASSIMP_TOOLS=OFF \
    -DASSIMP_BUILD_SAMPLES=OFF \
    -DASSIMP_NO_EXPORT=ON \
    -DASSIMP_SYSTEM_ZLIB=ON \
    -DASSIMP_BUILD_ZLIB=OFF

RUN cmake --build build --target install
