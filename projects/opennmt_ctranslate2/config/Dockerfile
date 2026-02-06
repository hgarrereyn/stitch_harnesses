ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates cmake ninja-build make \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install CTranslate2 as a shared library without extra backends
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz

RUN cmake -S /fuzz/src -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_CLI=OFF \
    -DWITH_MKL=OFF \
    -DWITH_DNNL=OFF \
    -DWITH_ACCELERATE=OFF \
    -DWITH_OPENBLAS=OFF \
    -DWITH_RUY=OFF \
    -DWITH_CUDA=OFF \
    -DOPENMP_RUNTIME=NONE \
    -DENABLE_CPU_DISPATCH=OFF \
 && cmake --build build --target install -- -v
