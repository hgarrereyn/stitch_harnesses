ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure, build and install Simd as a static library
WORKDIR /fuzz/build
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN cmake -S /fuzz/src/prj/cmake -B . \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DSIMD_TEST=OFF \
    -DSIMD_SHARED=OFF \
    -DSIMD_PYTHON=OFF \
    -DSIMD_OPENCV=OFF \
 && cmake --build . -j"$(nproc)" \
 && cmake --install .
