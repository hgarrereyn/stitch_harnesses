ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build/runtime dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    make \
    ninja-build \
    pkg-config \
    libssl-dev \
    zlib1g-dev \
    libsodium-dev \
    libreadline-dev \
    libncurses-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install SoftEtherVPN (libraries + tools)
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/build

# Configure
RUN cmake -S /fuzz/src -B /fuzz/build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=${CC} \
    -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install

# Build and install
RUN cmake --build /fuzz/build -j$(nproc) && cmake --install /fuzz/build

# Install headers for development (not installed by upstream)
RUN mkdir -p /fuzz/install/include/Cedar /fuzz/install/include/Mayaqua && \
    cp -a /fuzz/src/src/Cedar/*.h /fuzz/install/include/Cedar/ && \
    cp -a /fuzz/src/src/Mayaqua/*.h /fuzz/install/include/Mayaqua/ && \
    mkdir -p /fuzz/install/include/Mayaqua/Crypto && \
    cp -a /fuzz/src/src/Mayaqua/Crypto/*.h /fuzz/install/include/Mayaqua/Crypto/ && \
    cp -a /fuzz/src/src/GlobalConst.h /fuzz/install/include/
