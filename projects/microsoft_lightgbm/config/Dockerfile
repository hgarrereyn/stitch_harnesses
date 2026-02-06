ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3-pip ninja-build make build-essential \
 && rm -rf /var/lib/apt/lists/* \
 && pip3 install --no-cache-dir "cmake>=3.28"

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN cmake -S /fuzz/src -B /fuzz/build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DUSE_OPENMP=OFF \
    -DBUILD_CLI=OFF \
    -DBUILD_STATIC_LIB=ON \
 && cmake --build /fuzz/build --parallel \
 && cmake --install /fuzz/build
