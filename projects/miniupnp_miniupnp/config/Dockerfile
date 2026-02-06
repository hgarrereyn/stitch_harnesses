ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build miniupnpc (static) and install into /fuzz/install
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Configure and build only the static library
RUN cmake -S miniupnpc -B build-miniupnpc -G Ninja \
    -DCMAKE_C_COMPILER=${CC} \
    -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DUPNPC_BUILD_STATIC=ON \
    -DUPNPC_BUILD_SHARED=OFF \
    -DUPNPC_BUILD_TESTS=OFF \
    -DUPNPC_BUILD_SAMPLE=OFF \
 && cmake --build build-miniupnpc --target install -j$(nproc)
