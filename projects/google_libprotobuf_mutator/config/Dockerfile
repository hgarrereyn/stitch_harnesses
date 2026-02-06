ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential cmake ninja-build \
    protobuf-compiler libprotobuf-dev \
    liblzma-dev zlib1g-dev pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, and install libprotobuf-mutator (static libs, no tests/examples)
WORKDIR /fuzz/src
RUN cmake -S . -B build -GNinja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DLIB_PROTO_MUTATOR_TESTING=OFF \
    -DLIB_PROTO_MUTATOR_EXAMPLES=OFF \
    && cmake --build build --target install
