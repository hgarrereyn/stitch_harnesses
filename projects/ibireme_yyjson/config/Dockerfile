ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools if missing
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Configure, build static lib, and install to /fuzz/install
RUN cmake -S /fuzz/src -B /fuzz/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DYYJSON_BUILD_TESTS=OFF \
    -DYYJSON_BUILD_DOC=OFF \
    -DYYJSON_BUILD_MISC=OFF \
    -DYYJSON_BUILD_FUZZER=OFF && \
    cmake --build /fuzz/build --parallel && \
    cmake --install /fuzz/build
