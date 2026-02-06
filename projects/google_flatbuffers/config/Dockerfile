ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools (cmake, ninja)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install FlatBuffers static library
RUN cmake -S /fuzz/src -B /fuzz/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DFLATBUFFERS_BUILD_TESTS=OFF \
    -DFLATBUFFERS_BUILD_FLATC=OFF \
    -DFLATBUFFERS_BUILD_SHAREDLIB=OFF \
    -DFLATBUFFERS_INSTALL=ON \
 && cmake --build /fuzz/build --target install -j$(nproc)
