ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for S2OPC
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    pkg-config \
    libmbedtls-dev \
    libexpat1-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install S2OPC (Client/Server only, static libs)
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

RUN cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DS2OPC_CLIENTSERVER_ONLY=ON \
    -DENABLE_TESTING=OFF \
    -DENABLE_SAMPLES=OFF \
    -DWARNINGS_AS_ERRORS=OFF \
 && cmake --build build --target install -- -v
