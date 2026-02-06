ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        cmake ninja-build make build-essential unzip ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Configure and build opendnp3
WORKDIR /fuzz/src

# Configure
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DDNP3_STATIC_LIBS=ON \
    -DDNP3_TESTS=OFF \
    -DDNP3_EXAMPLES=OFF \
    -DDNP3_FUZZING=OFF \
    -DDNP3_TLS=OFF

# Build and install
RUN cmake --build build --target install --config Release
