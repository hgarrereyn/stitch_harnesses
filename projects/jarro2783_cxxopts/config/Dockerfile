ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools (header-only project, but we use CMake to install headers)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure and install with CMake
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCXXOPTS_ENABLE_INSTALL=ON \
    -DCXXOPTS_BUILD_EXAMPLES=OFF \
    -DCXXOPTS_BUILD_TESTS=OFF \
    -DCXXOPTS_USE_UNICODE_HELP=OFF \
 && cmake --build build --target install -- -v
