ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, install
WORKDIR /fuzz/src

RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DUSE_LIBFTDI=OFF \
    -DUSE_OPENMP=OFF \
    -DBUILD_OYMOTION_SDK=OFF \
    -DBUILD_SYNCHRONI_SDK=OFF \
    -DBUILD_BLUETOOTH=OFF \
    -DBUILD_BLE=OFF \
    -DBUILD_ONNX=OFF \
    -DBUILD_TESTS=OFF \
    -DBUILD_PERIPHERY=OFF

RUN cmake --build /fuzz/build --target install -j$(nproc)
