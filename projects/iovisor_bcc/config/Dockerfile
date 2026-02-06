ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    llvm-17-dev \
    libclang-17-dev \
    libelf-dev \
    zlib1g-dev \
    liblzma-dev \
    libdebuginfod-dev \
    bison \
    flex \
    pkg-config \
    git \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

WORKDIR /fuzz/src

RUN cmake -S . -B build -G Ninja \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_BUILD_TYPE=Release \
    -DENABLE_EXAMPLES=OFF \
    -DENABLE_TESTS=OFF \
    -DENABLE_MAN=OFF \
    -DENABLE_LLVM_SHARED=ON \
 && cmake --build build --target install
