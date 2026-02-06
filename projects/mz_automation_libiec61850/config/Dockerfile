ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
 && rm -rf /var/lib/apt/lists/*

# Configure and build libiec61850 as static library and install headers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz/src

RUN cmake -S . -B /fuzz/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=${CC} \
    -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_PYTHON_BINDINGS=OFF \
    -DCMAKE_BUILD_TYPE=Release \
 && cmake --build /fuzz/build --target install -j$(nproc)
