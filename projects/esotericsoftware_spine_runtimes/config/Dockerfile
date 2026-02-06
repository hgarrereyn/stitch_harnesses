ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools (cmake, ninja) and minimal dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
    make \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install spine-cpp (static library)
WORKDIR /fuzz/src/spine-cpp

RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
 && cmake --build build --target install --parallel

