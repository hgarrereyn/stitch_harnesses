ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    pkg-config \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install Glaze (header-only, interface target)
RUN cmake -S /fuzz/src -B /fuzz/build \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_TESTING=OFF \
    -Dglaze_DEVELOPER_MODE=OFF \
    -Dglaze_BUILD_EXAMPLES=OFF \
    -Dglaze_EETF_FORMAT=OFF \
    -Dglaze_ENABLE_SSL=OFF \
 && cmake --build /fuzz/build --parallel \
 && cmake --install /fuzz/build
