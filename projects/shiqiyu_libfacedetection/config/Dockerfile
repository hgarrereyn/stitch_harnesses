ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
    && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src

RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DUSE_OPENMP=OFF \
    -DENABLE_AVX2=OFF \
    -DENABLE_AVX512=OFF \
    -DENABLE_NEON=OFF && \
    cmake --build build --target install -- -v
