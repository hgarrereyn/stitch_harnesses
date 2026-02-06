ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies for building and using mlpack (header-only)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build pkg-config \
    libarmadillo-dev libopenblas-dev liblapack-dev \
    libensmallen-dev libcereal-dev \
    ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Configure and install headers into /fuzz/install
WORKDIR /fuzz/build
RUN cmake -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTS=OFF \
    -DBUILD_CLI_EXECUTABLES=OFF \
    -DBUILD_PYTHON_BINDINGS=OFF \
    -DBUILD_JULIA_BINDINGS=OFF \
    -DBUILD_GO_BINDINGS=OFF \
    -DBUILD_R_BINDINGS=OFF \
    -DBUILD_MARKDOWN_BINDINGS=OFF \
    /fuzz/src && \
    ninja -j$(nproc) install
