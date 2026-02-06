ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies (cmake, build tools, git for FetchContent)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make git ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install Brunsli
WORKDIR /fuzz/src

# Configure with LibAFL compiler wrappers and install prefix
RUN cmake -S . -B /fuzz/build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_TESTING=OFF

RUN cmake --build /fuzz/build --config Release -j$(nproc)
RUN cmake --install /fuzz/build --config Release
