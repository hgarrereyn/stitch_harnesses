ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools (cmake, ninja) and keep image minimal
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

# Configure, build, and install static library only
WORKDIR /fuzz/build
RUN cmake -G Ninja /fuzz/src \
    -DCMAKE_C_COMPILER=${CC} \
    -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED=OFF \
    -DBUILD_STATIC=ON \
    -DBUILD_TESTS=OFF \
    -DBUILD_FUZZERS=OFF \
    -DBUILD_BENCHMARKS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_PLUGINS=OFF
RUN cmake --build . --target install
