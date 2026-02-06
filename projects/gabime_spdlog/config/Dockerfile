ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install any extra build/runtime dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake make ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install spdlog as a static library
WORKDIR /fuzz/src
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DSPDLOG_BUILD_SHARED=OFF \
    -DBUILD_SHARED_LIBS=OFF \
    -DSPDLOG_BUILD_TESTS=OFF \
    -DSPDLOG_BUILD_EXAMPLE=OFF \
    -DSPDLOG_FMT_EXTERNAL=OFF \
    -DSPDLOG_FMT_EXTERNAL_HO=OFF \
 && cmake --build build --target install
