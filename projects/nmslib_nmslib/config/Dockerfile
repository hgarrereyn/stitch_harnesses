ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install the library
WORKDIR /fuzz/src/similarity_search
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DWITHOUT_TESTS=ON
RUN cmake --build build -j
RUN cmake --install build
