ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    pkg-config \
    libssl-dev \
    zlib1g-dev \
    libbrotli-dev \
    libuv1-dev \
    libwslay-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure and build
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src

RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=${CC} \
    -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DWITH_MRUBY=OFF \
    -DWITHOUT_LIBS=OFF

RUN cmake --build /fuzz/build --target install -j$(nproc)
