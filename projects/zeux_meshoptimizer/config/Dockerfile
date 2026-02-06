ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools (cmake, ninja)
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      cmake ninja-build && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure and build meshoptimizer as a static library
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DMESHOPT_BUILD_SHARED_LIBS=OFF \
    -DMESHOPT_BUILD_DEMO=OFF \
    -DMESHOPT_BUILD_GLTFPACK=OFF \
    -DMESHOPT_INSTALL=ON \
 && cmake --build build --config Release \
 && cmake --install build --config Release
