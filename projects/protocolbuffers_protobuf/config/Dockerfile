ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install protobuf (shared libs to simplify linking)
RUN cmake -S /fuzz/src -B /tmp/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -Dprotobuf_BUILD_SHARED_LIBS=ON \
    -DBUILD_SHARED_LIBS=ON \
    -Dprotobuf_WITH_ZLIB=OFF \
    -Dprotobuf_BUILD_TESTS=OFF \
    -Dprotobuf_BUILD_CONFORMANCE=OFF \
    -Dprotobuf_BUILD_EXAMPLES=OFF \
    -Dprotobuf_BUILD_PROTOC_BINARIES=OFF \
    -Dprotobuf_BUILD_LIBPROTOC=OFF \
    -Dprotobuf_VERBOSE=ON \
 && cmake --build /tmp/build --target install -j$(nproc) \
 && rm -rf /tmp/build
