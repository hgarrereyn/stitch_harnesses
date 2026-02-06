ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    perl \
    nasm \
    pkg-config \
    ninja-build \
    ca-certificates \
    libnuma-dev \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz/build
RUN cmake -G Ninja -S /fuzz/src -B /fuzz/build \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DQUIC_BUILD_SHARED=OFF \
    -DQUIC_BUILD_TEST=OFF \
    -DQUIC_BUILD_PERF=OFF \
    -DQUIC_BUILD_TOOLS=OFF \
    -DQUIC_USE_SYSTEM_LIBCRYPTO=OFF \
 && cmake --build . --target install
