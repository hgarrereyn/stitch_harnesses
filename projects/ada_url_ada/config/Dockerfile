ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools (cmake, ninja) if missing
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install ada as a static library
WORKDIR /fuzz/src
RUN cmake -S . -B /fuzz/build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DBUILD_SHARED_LIBS=OFF \
    -DADA_TESTING=OFF \
    -DADA_BENCHMARKS=OFF \
    -DADA_TOOLS=OFF \
    -DADA_USE_SIMDUTF=OFF \
 && cmake --build /fuzz/build --target install -j$(nproc)
