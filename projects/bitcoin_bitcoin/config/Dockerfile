ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    libboost-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install only the kernel static library
WORKDIR /fuzz/src

RUN cmake -S . -B /fuzz/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_BITCOIN_BIN=OFF \
    -DBUILD_DAEMON=OFF \
    -DBUILD_CLI=OFF \
    -DBUILD_TX=OFF \
    -DBUILD_UTIL=OFF \
    -DBUILD_TESTS=OFF \
    -DBUILD_GUI=OFF \
    -DENABLE_WALLET=OFF \
    -DWITH_ZMQ=OFF \
    -DENABLE_IPC=OFF \
    -DBUILD_KERNEL_LIB=ON \
    -DINSTALL_MAN=OFF

RUN cmake --build /fuzz/build --target bitcoinkernel -j$(nproc) && \
    cmake --install /fuzz/build
