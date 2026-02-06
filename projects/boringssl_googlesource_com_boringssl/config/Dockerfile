ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure and build BoringSSL (static), install to /fuzz/install
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN cmake -GNinja -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTING=OFF \
    -DFUZZ=OFF \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install
RUN ninja -C build install

# End