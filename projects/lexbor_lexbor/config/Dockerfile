ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends cmake ninja-build pkg-config build-essential && rm -rf /var/lib/apt/lists/*

# Configure, build, and install lexbor as a static library
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src

# Configure build: static only, no tests/examples/utils, install to /fuzz/install
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=${CC} \
    -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DLEXBOR_BUILD_SHARED=OFF \
    -DLEXBOR_BUILD_STATIC=ON \
    -DLEXBOR_BUILD_EXAMPLES=OFF \
    -DLEXBOR_BUILD_TESTS=OFF \
    -DLEXBOR_BUILD_UTILS=OFF

RUN cmake --build build --target install -- -v
